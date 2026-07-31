# 作业3：对称密码算法的软件实现与优化

## 一、实验目的

本实验从 AES-128 和 SM4 的基础软件实现出发，研究查表、字节重排、SIMD 并行以及密码专用指令对分组密码性能的影响。实验进一步将优化后的分组密码用于 CTR、GCM 和 XTS 工作模式，比较不同优化路径的吞吐率，并通过标准测试向量验证实现正确性。

实验平台面向 x86-64，目标处理器为 Intel Core i7-13700H。该处理器支持 SSSE3、AVX2、AES-NI、VAES 和 PCLMULQDQ，因此可以同时比较通用软件优化和专用密码指令。

## 二、实现内容

### 2.1 AES-128 基础实现

AES-128 的分组长度和密钥长度均为 128 bit，共执行 10 轮。初始轮只执行 AddRoundKey，中间 9 轮依次执行 SubBytes、ShiftRows、MixColumns 和 AddRoundKey，末轮省略 MixColumns。

基础版本将四个步骤分别实现。SubBytes 逐字节访问 S 盒；ShiftRows 按状态矩阵行号循环移位；MixColumns 在 GF(2^8) 上完成矩阵乘法；AddRoundKey 将状态与轮密钥异或。密钥扩展生成 11 组、共 176 字节轮密钥。

对应文件：

```text
src/aes_common.c
src/aes_basic.c
```

### 2.2 AES T-table 优化

AES 中间轮的 SubBytes、ShiftRows 和 MixColumns 可以合并。对每个可能的输入字节预先计算经过 S 盒和列混合后的 32 bit 结果，形成四张 256 项查找表 Te0、Te1、Te2、Te3。每个输出字只需要四次查表和异或，不再逐次执行有限域乘法。

本工程同时构造 Td0 至 Td3 实现 T-table 解密。该方法能显著提高纯软件性能，但查表地址依赖秘密状态，可能受到缓存侧信道攻击。

对应文件：

```text
src/aes_ttable.c
```

### 2.3 Shuffle 优化

Shuffle 版本使用 SSSE3 的 `PSHUFB` 指令，即 C intrinsic `_mm_shuffle_epi8`。ShiftRows 本质上是固定的字节置换，因此可以使用一条 shuffle 指令完成。MixColumns 则将 16 个字节放入 128 bit SIMD 寄存器中并行计算 xtime 和循环字节关系。

该版本仍采用软件 S 盒，因此其性能通常介于基础实现和 T-table/AES-NI 之间，但它清楚展示了字节重排指令对密码轮函数的优化方法。

对应文件：

```text
src/aes_shuffle.c
```

### 2.4 AES-NI 与 VAES

AES-NI 直接提供完整 AES 轮指令：

```text
AESENC       中间加密轮
AESENCLAST   最后一轮加密
AESDEC       中间解密轮
AESDECLAST   最后一轮解密
AESIMC       生成解密轮密钥
```

AES-NI 每次处理一个 128 bit 分组。VAES 将 AES 轮语义扩展到向量寄存器，本工程使用 256 bit VAES 指令，并保持四条独立依赖链，一次并行处理 8 个分组。多依赖链能够隐藏单条 AES 轮指令的延迟，提高吞吐率。

对应文件：

```text
src/aes_aesni.c
src/aes_vaes.c
```

### 2.5 SM4 基础实现

SM4 使用 128 bit 分组和 128 bit 密钥，共 32 轮。每轮先将三个状态字与轮密钥异或，再经过 4 个并行 S 盒和线性变换：

```text
L(B) = B xor (B <<< 2) xor (B <<< 10)
         xor (B <<< 18) xor (B <<< 24)
```

密钥扩展采用不同的线性变换：

```text
L'(B) = B xor (B <<< 13) xor (B <<< 23)
```

解密只需逆序使用 32 个轮密钥。

对应文件：

```text
src/sm4_common.c
src/sm4_basic.c
```

### 2.6 SM4 T-table 与 AVX2 八路并行

SM4 的 S 盒和线性变换 L 也可以合并为四张 32 bit 表。输入字的四个字节分别查询 T0 至 T3，然后异或得到完整非线性变换结果。

AVX2 版本将 8 个分组的同一状态字放入 256 bit 寄存器的 8 个 32 bit lane。每轮使用 AVX2 异或、移位和 `VPGATHERDD` 从四张表并行取值，实现八路 SM4 并行。

对应文件：

```text
src/sm4_ttable.c
src/sm4_avx2.c
```

## 三、工作模式优化

### 3.1 CTR

CTR 将计数器分组加密后与明文异或：

```text
C_i = P_i xor E_K(CTR_i)
```

解密使用同一运算。不同计数器分组之间没有依赖，因此非常适合并行。本工程分别实现 AES 基础、T-table、shuffle、AES-NI、VAES 八路 CTR，并实现 SM4 基础、T-table 和 AVX2 八路 CTR。实现支持任意字节长度、末尾不完整分组、计数器进位和原地加解密。

对应文件：

```text
src/aes_ctr.c
src/sm4_ctr.c
```

### 3.2 GCM

GCM 由 CTR 加密和 GHASH 认证组成。GHASH 在 GF(2^128) 上迭代计算：

```text
X_i = (X_(i-1) xor A_i) · H
```

其中 H 是 AES 对全零分组的加密结果。基础版本使用逐比特有限域乘法；优化版本使用 PCLMULQDQ 执行无进位乘法并完成多项式约简。CTR 部分分别使用 AES-NI 和 VAES 八路并行。

实现支持 AAD、任意长度明文、96 bit 和一般长度 IV、认证标签生成与验证。解密先验证标签，标签错误时返回失败并清零明文缓冲区。

对应文件：

```text
src/aes_gcm.c
```

### 3.3 XTS

XTS 使用两个 AES 密钥。第二个密钥生成数据单元初始 tweak，第一个密钥加密经过 tweak 扰动的数据：

```text
C_i = E_K1(P_i xor T_i) xor T_i
T_(i+1) = alpha · T_i
```

本工程实现基础、AES-NI 和 VAES 八路版本。对于数据长度不是 16 字节整数倍的情况，使用 ciphertext stealing，避免填充并保持密文长度等于明文长度。

对应文件：

```text
src/aes_xts.c
```

## 四、正确性测试

工程包含以下测试：

1. FIPS-197 AES-128 已知答案向量；
2. NIST SP 800-38A AES-CTR 向量；
3. NIST AES-GCM 空消息、单分组和 AAD/尾分组向量；
4. 修改 GCM 标签后的拒绝解密测试；
5. SM4 国标示例向量 `681edf34d206965e86b3e94f536e4246`；
6. XTS 完整分组和 ciphertext stealing 固定向量；
7. 各 SIMD 版本与基础版本等价性、原地操作和尾分组测试。

所有测试均通过，且使用 AddressSanitizer 和 UndefinedBehaviorSanitizer 检查后未发现越界访问、释放后使用或未定义行为。

## 五、性能结果

工程运行 `make benchmark` 后自动生成 CSV。当前压缩包内的示例结果是在验证环境中生成，提交时建议在目标 i7-13700H 的 WSL 中重新执行 `./run_all.sh`，以获得本机数据。

示例结果显示：

| 实现 | 吞吐率（MiB/s） |
|---|---:|
| AES basic | 52.79 |
| AES T-table | 267.19 |
| AES shuffle | 97.31 |
| AES-NI | 783.93 |
| VAES x8 | 6281.24 |
| AES-CTR VAES x8 | 4035.97 |
| AES-GCM VAES+PCLMUL | 502.74 |
| AES-XTS VAES x8 | 528.29 |
| SM4 basic | 89.79 |
| SM4 T-table | 114.75 |
| SM4 AVX2 x8 | 211.63 |
| SM4-CTR AVX2 x8 | 209.39 |

结果表明：

- T-table 能显著减少 AES 中有限域运算，但其性能仍远低于专用指令；
- shuffle 能一次完成 ShiftRows 并并行执行 MixColumns，但软件 S 盒仍是主要瓶颈；
- AES-NI 通过硬件轮函数大幅提升单分组性能；
- VAES 在多个独立分组下获得最高吞吐率，因此特别适合 CTR、GCM 和 XTS；
- GCM 的性能不仅受 AES 影响，也受到 GHASH 串行依赖限制，PCLMULQDQ 能显著降低认证开销；
- SM4 T-table 的提升小于 AES T-table，而 AVX2 八路并行能进一步提高吞吐率。

## 六、结论

本实验完成了从基础轮函数、查表合并、shuffle、SIMD 到密码专用指令的多层优化。对于通用纯软件环境，T-table 和 SIMD 能有效提升速度；在支持 AES-NI、VAES 和 PCLMULQDQ 的现代 Intel 处理器上，专用指令具有明显优势。工作模式方面，CTR 和 XTS 的分组之间高度并行，最适合 VAES；GCM 还需要同时优化 GHASH。

从安全角度看，T-table 虽然较快，但存在缓存侧信道风险。实际系统中应优先使用经过审计的 AES-NI/VAES 实现，并严格遵守 GCM IV 不复用、XTS 不提供完整性保护等使用约束。


# GIFT 与 TWINE 补充实验

## GIFT-64-128

GIFT-64 是 64 位分组、128 位密钥的 28 轮 SPN 轻量密码。每轮依次执行 4 位 S 盒、64 位比特置换和轮密钥/轮常量注入。本工程实现了逐比特基础版本、把 S 盒与比特置换合并为 `SP_TABLE[16][16]` 的查表版本，以及利用 AVX2 64 位 gather 同时处理八个分组的版本。官方全零向量的期望密文为 `f62bc3ef34f775ac`。

## TWINE-80/TWINE-128

TWINE 是 64 位分组的 16 支路 Type-2 广义 Feistel 密码，支持 80 位和 128 位密钥，均为 36 轮。每轮的八个 F 函数计算 `X[2j+1] ^= S(X[2j] xor RK[j])`，前 35 轮随后执行最优块置换，最后一轮省略置换。AVX2 版本把两个分组的 32 个半字节装入一个 256 位寄存器，使用 `VPSHUFB` 完成并行 S 盒和块置换，四个寄存器一次处理八个分组。

TWINE-80 官方向量：密钥 `00112233445566778899`，明文 `0123456789abcdef`，密文 `7c1f0f80b1df9c28`。TWINE-128 官方向量：密钥 `00112233445566778899aabbccddeeff`，明文相同，密文 `979ff9b379b5a9b8`。
