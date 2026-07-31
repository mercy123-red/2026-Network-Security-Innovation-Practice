# 作业3：对称密码算法的软件实现与优化

本工程面向 **WSL Ubuntu + Intel Core i7-13700H**，完整实现并比较 AES、SM4、GIFT、TWINE 四种分组密码，以及 CTR、GCM、XTS 工作模式的软件执行效率。

## 1. 作业要求覆盖情况

| 作业要求 | 本工程实现 |
|---|---|
| 基本实现 | AES-128、SM4、GIFT-64-128、TWINE-80/TWINE-128 完整逐轮实现 |
| T-table | AES 四张 Te/Td 表；SM4 四张 T 表；GIFT 合并 SubCells+PermBits 的 SP 表 |
| shuffle | AES 使用 `PSHUFB` 完成 ShiftRows；TWINE 使用 AVX2 `VPSHUFB` 并行执行 S 盒与块置换 |
| 新指令集方法一 | AES-NI：`AESENC/AESENCLAST/AESDEC/AESDECLAST` |
| 新指令集方法二 | VAES + AVX2：一次处理 8 个 AES 分组 |
| GCM 专用指令 | `PCLMULQDQ` 加速 GHASH |
| CTR | AES 基础/T-table/shuffle/AES-NI/VAES；SM4 基础/T-table/AVX2 |
| GCM | 基础 AES+GHASH、AES-NI+PCLMUL、VAES+PCLMUL |
| XTS | 基础、AES-NI、VAES；支持 ciphertext stealing |
| 正确性验证 | FIPS-197、NIST CTR/GCM、SM4 国标示例、GIFT 官方向量、TWINE 原论文向量、XTS 固定向量 |
| 性能测试 | 自动输出 CSV，并生成横向柱状图 |

## 2. 目录结构

```text
SymmetricCryptoOptimization_Final/
├── include/                 公共头文件
│   ├── aes.h
│   ├── aes_ctr.h
│   ├── aes_gcm.h
│   ├── aes_xts.h
│   ├── sm4.h
│   ├── sm4_ctr.h
│   ├── gift64.h
│   └── twine.h
├── src/
│   ├── aes_basic.c          AES 基本实现
│   ├── aes_ttable.c         AES T-table
│   ├── aes_shuffle.c        PSHUFB shuffle 优化
│   ├── aes_aesni.c          AES-NI
│   ├── aes_vaes.c           VAES 八分组并行
│   ├── aes_ctr.c
│   ├── aes_gcm.c
│   ├── aes_xts.c
│   ├── sm4_basic.c
│   ├── sm4_ttable.c
│   ├── sm4_avx2.c
│   ├── sm4_ctr.c
│   ├── gift64.c           GIFT-64 基础/T-table/AVX2 x8
│   └── twine.c            TWINE-80/128 基础/AVX2 x8
├── tests/                   正确性测试与 benchmark
├── scripts/                 CSV 合并与画图脚本
├── results/                 已生成的性能结果和图片
├── report/REPORT.md         可直接用于实验报告的内容
├── Makefile
└── run_all.sh               一键编译、测试、性能测试、画图
```

## 3. WSL 一键运行

```bash
unzip SymmetricCryptoOptimization_AllFour.zip
cd SymmetricCryptoOptimization_AllFour
./run_all.sh
```

如果出现没有执行权限：

```bash
chmod +x run_all.sh
./run_all.sh
```

仅编译和正确性测试：

```bash
make clean
make -j"$(nproc)"
make test
```

正式性能测试：

```bash
make benchmark
```

画图需要 `matplotlib`。若 WSL 尚未安装：

```bash
python3 -m pip install matplotlib
make plot
```

## 4. 输出文件

运行后生成：

```text
results/aes_benchmark.csv
results/ctr_benchmark.csv
results/gcm_benchmark.csv
results/xts_benchmark.csv
results/sm4_benchmark.csv
results/lightweight_benchmark.csv
results/all_benchmarks.csv
results/performance.png
```

## 5. 验证情况

工程已经完成以下检查：

- `-O3 -Wall -Wextra -Wpedantic` 零警告编译；
- AES、CTR、GCM、XTS、SM4、SM4-CTR、GIFT-64、TWINE-80/128 全部正确性测试通过；
- GCM 修改认证标签后能够拒绝解密并清零输出；
- CTR 和 XTS 支持原地操作及非整分组尾部；
- AddressSanitizer 与 UndefinedBehaviorSanitizer 全部通过。

详细日志：

```text
VERIFIED_ALLFOUR_TEST_OUTPUT.txt
VERIFIED_ALLFOUR_SANITIZER_OUTPUT.txt
VERIFIED_ALLFOUR_RELEASE_BENCHMARK_OUTPUT.txt
```

## 6. 安全说明

T-table 根据秘密数据索引内存，可能泄漏缓存访问模式，因此适合课程性能对比，不建议用于有缓存侧信道威胁的生产系统。AES-NI 和 VAES 通常既更快，也避免了传统 T-table 的秘密相关查表。GCM 必须保证同一密钥下 IV 不重复；XTS 用于存储加密，不提供完整性认证。

## WSL 无图形界面说明

绘图脚本固定使用 Matplotlib 的 `Agg` 后端，因此不依赖 Qt/X11。若只需重新生成图表，可执行：

```bash
MPLBACKEND=Agg make plot
```


## 7. GIFT 与 TWINE 补充实现

- **GIFT-64-128**：64 位分组、128 位密钥、28 轮；提供基础加解密、将 SubCells 与 PermBits 合并的 SP-table，以及 AVX2 gather 八分组并行版本。
- **TWINE-80/TWINE-128**：64 位分组、80/128 位密钥、36 轮；提供基础加解密和 AVX2 `VPSHUFB` 八分组并行版本。
- GIFT 使用项目官方零向量 `0000000000000000 -> f62bc3ef34f775ac` 验证；TWINE 使用原论文附录中的 80/128 位密钥测试向量验证。
