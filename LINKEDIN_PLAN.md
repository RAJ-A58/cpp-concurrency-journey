# LinkedIn Learning & Sharing Tracker

Publicly documenting low-latency C++ projects is one of the highest-leverage ways to stand out to quant firms and prop shops.

### Weekly Posting Cadence

| Phase | Week | Topic / Deliverable | Post Hook & Summary |
|---|---|---|---|
| **Phase 1** | Week 1 | Thread-safe Blocking Queue | Why naive mutex queues hurt throughput and how condition variables work |
| | Week 2 | Work-Stealing Thread Pool | Balancing tasks across worker threads in modern C++20 |
| | Week 3 | Parallel Merge Sort | Cache locality and overhead considerations in parallel divide-and-conquer |
| **Phase 2** | Week 4 | Atomics & CAS Loops | Spinlocks vs. OS Mutexes: When does busy-waiting actually pay off? |
| | Week 5 | Memory Ordering: Acquire-Release vs Seq_Cst | Breaking down the assembly on x86-64 vs ARM (Store Buffers & Fences) |
| | Week 6 | The ABA Problem & Solutions | Hazard pointers vs tagged pointers |
| **Phase 3** | Week 7 | False Sharing & Cache Lines | How two independent counters killed multi-core scaling (with benchmarks) |
| | Week 8 | Thread Pinning & CPU Affinity | Eliminating context switches with `pthread_setaffinity_np` |
| **Phase 4** | Week 9 | Lock-Free SPSC Queue | Step-by-step whiteboard explanation of an SPSC ring buffer |
| | Week 10 | Disruptor Pattern in C++ | Sequence barriers and ring-buffer architectures for trading engines |
| **Phase 5** | Week 11 | Order Book + Latency Benchmarks | Profiling $p99$ tail latency with Google Benchmark and Linux `perf` |
