#include "openfhe.h"

#include <algorithm>
#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace lbcrypto;

namespace {

constexpr size_t kImageH = 4;
constexpr size_t kImageW = 4;
constexpr size_t kKernelH = 3;
constexpr size_t kKernelW = 3;
constexpr size_t kOutH = kImageH - kKernelH + 1;
constexpr size_t kOutW = kImageW - kKernelW + 1;
constexpr size_t kBatchSize = kImageH * kImageW;

struct RotationStats {
    std::string name;
    size_t rotations = 0;
    std::vector<int32_t> indices;

    explicit RotationStats(std::string methodName) : name(std::move(methodName)) {}
};

size_t RowMajor(size_t row, size_t col, size_t width = kImageW) {
    return row * width + col;
}

std::vector<size_t> SparseOutputSlots() {
    std::vector<size_t> slots;
    for (size_t r = 0; r < kOutH; ++r) {
        for (size_t c = 0; c < kOutW; ++c) {
            slots.push_back(RowMajor(r, c));
        }
    }
    return slots;  // {0, 1, 4, 5}
}

Plaintext MakeMask(const CryptoContext<DCRTPoly>& cc,
                   const std::vector<size_t>& slots,
                   double value) {
    std::vector<double> mask(kBatchSize, 0.0);
    for (const auto slot : slots) {
        if (slot >= mask.size()) {
            throw std::out_of_range("mask slot is out of range");
        }
        mask[slot] = value;
    }
    return cc->MakeCKKSPackedPlaintext(mask);
}

Ciphertext<DCRTPoly> Rotate(const CryptoContext<DCRTPoly>& cc,
                            const Ciphertext<DCRTPoly>& ct,
                            int32_t index,
                            RotationStats& stats) {
    if (index == 0) {
        return ct;
    }
    ++stats.rotations;
    stats.indices.push_back(index);
    return cc->EvalRotate(ct, index);
}

std::vector<double> PlainConv2x2(const std::vector<double>& input,
                                 const std::vector<double>& kernel) {
    std::vector<double> out(kOutH * kOutW, 0.0);
    for (size_t oh = 0; oh < kOutH; ++oh) {
        for (size_t ow = 0; ow < kOutW; ++ow) {
            double sum = 0.0;
            for (size_t kh = 0; kh < kKernelH; ++kh) {
                for (size_t kw = 0; kw < kKernelW; ++kw) {
                    const size_t inputIndex = RowMajor(oh + kh, ow + kw);
                    const size_t kernelIndex = RowMajor(kh, kw, kKernelW);
                    sum += input[inputIndex] * kernel[kernelIndex];
                }
            }
            out[RowMajor(oh, ow, kOutW)] = sum;
        }
    }
    return out;
}

Ciphertext<DCRTPoly> EncryptedConvDirect(const CryptoContext<DCRTPoly>& cc,
                                         const Ciphertext<DCRTPoly>& ctInput,
                                         const std::vector<double>& kernel,
                                         RotationStats& stats) {
    const auto outSlots = SparseOutputSlots();
    Ciphertext<DCRTPoly> acc;
    bool first = true;

    for (size_t kh = 0; kh < kKernelH; ++kh) {
        for (size_t kw = 0; kw < kKernelW; ++kw) {
            const auto offset = static_cast<int32_t>(RowMajor(kh, kw));
            const auto shifted = Rotate(cc, ctInput, offset, stats);
            const auto weight = kernel[RowMajor(kh, kw, kKernelW)];
            const auto mask = MakeMask(cc, outSlots, weight);
            const auto term = cc->EvalMult(shifted, mask);

            if (first) {
                acc = term;
                first = false;
            } else {
                acc = cc->EvalAdd(acc, term);
            }
        }
    }

    return acc;
}

std::vector<size_t> RowShiftedOutputSlots(size_t kernelRow) {
    std::vector<size_t> slots;
    const size_t rowShift = kernelRow * kImageW;
    for (const auto baseSlot : SparseOutputSlots()) {
        slots.push_back(baseSlot + rowShift);
    }
    return slots;
}

Ciphertext<DCRTPoly> EncryptedConvBabyGiant(const CryptoContext<DCRTPoly>& cc,
                                            const Ciphertext<DCRTPoly>& ctInput,
                                            const std::vector<double>& kernel,
                                            RotationStats& stats) {
    // Baby steps: create the three horizontal alignments x[i], x[i+1], x[i+2].
    std::vector<Ciphertext<DCRTPoly>> baby(kKernelW);
    baby[0] = ctInput;
    baby[1] = Rotate(cc, ctInput, 1, stats);
    baby[2] = Rotate(cc, ctInput, 2, stats);

    Ciphertext<DCRTPoly> acc;
    bool firstRow = true;

    for (size_t kh = 0; kh < kKernelH; ++kh) {
        Ciphertext<DCRTPoly> rowSum;
        bool firstCol = true;
        const auto rowSlots = RowShiftedOutputSlots(kh);

        for (size_t kw = 0; kw < kKernelW; ++kw) {
            const auto weight = kernel[RowMajor(kh, kw, kKernelW)];
            const auto mask = MakeMask(cc, rowSlots, weight);
            const auto term = cc->EvalMult(baby[kw], mask);

            if (firstCol) {
                rowSum = term;
                firstCol = false;
            } else {
                rowSum = cc->EvalAdd(rowSum, term);
            }
        }

        const auto verticalShift = static_cast<int32_t>(kh * kImageW);
        const auto alignedRow = Rotate(cc, rowSum, verticalShift, stats);
        if (firstRow) {
            acc = alignedRow;
            firstRow = false;
        } else {
            acc = cc->EvalAdd(acc, alignedRow);
        }
    }

    return acc;
}

Ciphertext<DCRTPoly> CompactSparse2x2ToFirst4Slots(const CryptoContext<DCRTPoly>& cc,
                                                   const Ciphertext<DCRTPoly>& sparse,
                                                   RotationStats& stats) {
    const auto low = cc->EvalMult(sparse, MakeMask(cc, {0, 1}, 1.0));
    const auto high = cc->EvalMult(sparse, MakeMask(cc, {4, 5}, 1.0));
    const auto highMoved = Rotate(cc, high, 2, stats);
    return cc->EvalAdd(low, highMoved);
}

std::vector<double> DecryptRealSlots(const CryptoContext<DCRTPoly>& cc,
                                     const PrivateKey<DCRTPoly>& sk,
                                     const Ciphertext<DCRTPoly>& ct,
                                     size_t length) {
    Plaintext pt;
    cc->Decrypt(sk, ct, &pt);
    pt->SetLength(length);

    const auto packed = pt->GetCKKSPackedValue();
    std::vector<double> values(length);
    for (size_t i = 0; i < length; ++i) {
        values[i] = std::real(packed[i]);
    }
    return values;
}

void PrintMatrix(const std::string& title,
                 const std::vector<double>& values,
                 size_t rows,
                 size_t cols) {
    std::cout << title << "\n";
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            const double value = values[RowMajor(r, c, cols)];
            if (std::abs(value - std::round(value)) < 1e-6) {
                std::cout << std::setw(8) << static_cast<long long>(std::llround(value)) << " ";
            } else {
                std::cout << std::setw(10) << std::fixed << std::setprecision(4) << value << " ";
            }
        }
        std::cout << "\n";
    }
}

void PrintSparseOutput(const std::string& title, const std::vector<double>& slots) {
    std::vector<double> out = {
        slots[0],
        slots[1],
        slots[4],
        slots[5],
    };
    PrintMatrix(title, out, kOutH, kOutW);
}

bool Check2x2(const std::vector<double>& got,
              const std::vector<double>& expected,
              const std::vector<size_t>& gotSlots,
              double eps,
              double& maxErr) {
    maxErr = 0.0;
    for (size_t i = 0; i < expected.size(); ++i) {
        const double err = std::abs(got[gotSlots[i]] - expected[i]);
        maxErr = std::max(maxErr, err);
    }
    return maxErr <= eps;
}

void PrintRotationStats(const RotationStats& stats) {
    std::cout << stats.name << "：" << stats.rotations << " 次，旋转索引 = [";
    for (size_t i = 0; i < stats.indices.size(); ++i) {
        std::cout << stats.indices[i];
        if (i + 1 != stats.indices.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

void PrintTheoryNote() {
    std::cout << "\n结论：\n";
    std::cout << "直接法需要 8 次卷积旋转。\n";
    std::cout << "在单密文、无重复编码、9 个权重均非零的模型下，理论下界为 ceil(log2(9)) = 4。\n";
    std::cout << "优化法需要 4 次卷积旋转，因此在上述模型下达到理论最小值。\n";
    std::cout << "输出从 [0,1,4,5] 整理到 [0,1,2,3] 还要额外 1 次旋转，但这一步不计入卷积计算。\n";
}

}  // namespace

int main() {
    const std::vector<double> input = {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 11, 12,
        13, 14, 15, 16,
    };

    const std::vector<double> kernel = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    };

    const auto expected = PlainConv2x2(input, kernel);

    CCParams<CryptoContextCKKSRNS> parameters;
    parameters.SetMultiplicativeDepth(2);
    parameters.SetScalingModSize(50);
    parameters.SetBatchSize(kBatchSize);

    const auto cc = GenCryptoContext(parameters);
    cc->Enable(PKE);
    cc->Enable(KEYSWITCH);
    cc->Enable(LEVELEDSHE);
    cc->Enable(ADVANCEDSHE);

    const auto keys = cc->KeyGen();
    cc->EvalMultKeyGen(keys.secretKey);

    // Positive OpenFHE rotations shift packed slots left: slot i receives old slot i + index.
    cc->EvalRotateKeyGen(keys.secretKey, {1, 2, 4, 5, 6, 8, 9, 10});

    const auto ptInput = cc->MakeCKKSPackedPlaintext(input);
    const auto ctInput = cc->Encrypt(keys.publicKey, ptInput);

    std::cout << "===== OpenFHE 密文卷积实验 =====\n";
    std::cout << "输入规模：4x4，卷积核：3x3，步长：1，无填充\n\n";
    PrintMatrix("明文卷积结果：", expected, kOutH, kOutW);

    RotationStats directStats("直接法");
    const auto directCt = EncryptedConvDirect(cc, ctInput, kernel, directStats);
    const auto directSlots = DecryptRealSlots(cc, keys.secretKey, directCt, kBatchSize);
    PrintSparseOutput("\n密文卷积结果（直接法）：", directSlots);

    RotationStats bgStats("优化法");
    const auto bgCt = EncryptedConvBabyGiant(cc, ctInput, kernel, bgStats);
    const auto bgSlots = DecryptRealSlots(cc, keys.secretKey, bgCt, kBatchSize);

    RotationStats compactStats("输出整理");
    const auto compactCt = CompactSparse2x2ToFirst4Slots(cc, bgCt, compactStats);
    const auto compactSlots = DecryptRealSlots(cc, keys.secretKey, compactCt, kBatchSize);
    PrintSparseOutput("\n密文卷积结果（优化法）：", bgSlots);

    double directErr = 0.0;
    double bgErr = 0.0;
    double compactErr = 0.0;
    const bool directOk = Check2x2(directSlots, expected, SparseOutputSlots(), 1e-4, directErr);
    const bool bgOk = Check2x2(bgSlots, expected, SparseOutputSlots(), 1e-4, bgErr);
    const bool compactOk = Check2x2(compactSlots, expected, {0, 1, 2, 3}, 1e-4, compactErr);
    const bool ok = directOk && bgOk && compactOk;

    std::cout << "\n正确性验证：\n";
    std::cout << std::scientific << std::setprecision(15);
    std::cout << "直接法最大误差：" << directErr
              << "，" << (directOk ? "通过" : "未通过") << "\n";
    std::cout << "优化法最大误差：" << bgErr
              << "，" << (bgOk ? "通过" : "未通过") << "\n";
    std::cout << "连续槽位输出最大误差：" << compactErr
              << "，" << (compactOk ? "通过" : "未通过") << "\n";

    std::cout << "\n旋转次数统计：\n";
    PrintRotationStats(directStats);
    PrintRotationStats(bgStats);
    PrintRotationStats(compactStats);
    PrintTheoryNote();

    return ok ? 0 : 1;
}
