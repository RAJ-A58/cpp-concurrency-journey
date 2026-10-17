# Hardware Baseline & Environment Notes

Captured: October 2026

## CPU Architecture
- **Model:** 13th Gen Intel(R) Core(TM) i5-13450HX
- **Architecture:** x86_64 (Little Endian)
- **Cores / Threads:** 10 Cores (6 P-cores + 4 E-cores), 16 Threads
- **Clock Speed:** 800 MHz min / 4600 MHz max
- **NUMA Nodes:** 1

## Cache Hierarchy
- **L1d Cache:** 416 KiB total (10 instances) — 64-byte line size
- **L1i Cache:** 448 KiB total (10 instances)
- **L2 Cache:** 9.5 MiB (7 instances)
- **L3 Cache:** 20 MiB shared (1 instance)

## Toolchain Verification
- **C++ Standard:** C++20 (`-std=c++20`)
- **Compilers:** `g++` and `clang++`
- **Sanitizers:**
  - `clang++ -fsanitize=thread` works out of the box
  - GCC TSan: run with `setarch $(uname -m) -R ./binary` or compile with Clang due to Linux 6.x ASLR high entropy.
