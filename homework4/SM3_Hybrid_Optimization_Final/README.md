# 作业4：SM3 软件实现与 SIMD/GPR 混合优化

本工程实现完整的 SM3 哈希算法，并提供 ARM64 与 x86-64 两类架构的 SIMD/通用寄存器混合优化。所有优化版本均与标量基准实现交叉验证。

## 1. 实现内容

| 架构 | 实现 | SIMD并行宽度 | 主要文件 |
|---|---|---:|---|
| 通用 | 标量/GPR 基线 | 1路 | `src/sm3_scalar.c` |
| x86-64 | AVX2 混合优化 | 8路独立消息 | `src/x86/sm3_avx2.c` |
| x86-64 | AVX-512F 混合优化 | 16路独立消息 | `src/x86/sm3_avx512.c` |
| ARM64 | NEON 混合优化 | 4路独立消息 | `src/arm64/sm3_neon.c` |

“混合”体现在：

1. 通用寄存器负责输入长度、填充、分组地址、大小端转换和 SIMD lane 转置；
2. SIMD寄存器同时保存多条独立消息的 `A~H` 状态和 `W/W'` 消息扩展字；
3. 64轮压缩函数中的布尔函数、模加、循环移位和置换由 SIMD 指令并行执行；
4. 不足一个 SIMD 批次的消息由标量实现收尾，形成可用的混合调度框架。

由于同一条 SM3 消息的分组存在链式依赖，本工程采用密码库中常见的 multi-buffer 方法，在多条独立消息之间提取并行度，而不是错误地并行同一消息的相邻分组。

## 2. 正确性测试

包含以下测试：

- SM3 空串标准向量；
- `abc` 标准向量；
- `abcd` 重复16次标准向量；
- 流式 `init/update/final` 与一次性接口一致性；
- 长度为 0、3、55、56、63、64、65、127、128、129、1000 字节时，各 SIMD 后端与标量实现逐消息比较；
- 自动运行时派发及不足 SIMD 批次的标量尾处理。

## 3. x86-64 / WSL 编译运行

```bash
unzip SM3_Hybrid_Optimization_Final.zip
cd SM3_Hybrid_Optimization_Final
chmod +x run_all.sh
./run_all.sh
```

也可以分步运行：

```bash
make -j$(nproc)
make test
./sm3_benchmark 16 results/sm3_benchmark.csv
make plot
```

程序通过 `__builtin_cpu_supports` 进行运行时检测。没有 AVX-512 的 CPU 会正常跳过 AVX-512 测试，不会执行非法指令。Intel Core i7-13700H 支持 AVX2，但通常不开放 AVX-512，因此预期 AVX2 运行、AVX-512 显示 `SKIP`。

## 4. ARM64 编译运行

在 ARM64 Linux 开发板或服务器上：

```bash
make clean
make -j$(nproc)
make test
make benchmark
make plot
```

Makefile 会根据 `uname -m` 自动选择 `src/arm64/sm3_neon.c`。ARM64 的 Advanced SIMD/NEON 是 AArch64 基础架构的一部分。

在 x86 主机上可用 Clang 对 ARM64 NEON 源码做语法检查：

```bash
make arm64-syntax
```

这只能验证交叉编译语法，ARM64 性能数据必须在真实 ARM64 设备上采集。

## 5. 输出文件

```text
results/sm3_benchmark.csv
results/sm3_performance.png
```

CSV 中记录实现名称、并行lane数、吞吐率、相对标量加速比与校验值。

## 6. 安全与工程说明

- SM3 不使用秘密密钥，消息相关内存访问的侧信道风险与分组密码查表实现不同；
- 本实现不使用未定义的未对齐整数解引用，大小端读取显式完成；
- AVX2/AVX-512 代码分别放在带专用编译选项的目标文件中，并在运行前检查 CPU 能力；
- 多缓冲接口要求同一批消息长度相等，便于保持 SIMD lane 同步；任意剩余消息自动由标量路径完成；
- 工程用于课程实验和体系结构优化学习，生产环境仍建议使用经过长期审计的密码库。
