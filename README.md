# C++ Concurrency & Low-Latency Journey for Quant Dev

**Author:** [RAJ-A58](https://github.com/RAJ-A58)  
**Target:** Low-Latency / HFT / Trading Systems C++ Engineer  
**Started:** October 2026  

---

## 🎯 Roadmap Overview

- **Phase 1: Fundamentals (Weeks 1–3)**
  - `std::thread`, `std::mutex`, `std::condition_variable`, `std::future` / promises
  - C++20 additions: `std::jthread`, `std::stop_token`, latches, barriers, semaphores
  - Projects: Thread Pool, Thread-Safe Blocking Queue, Parallel Merge Sort
- **Phase 2: Memory Model & Atomics (Weeks 4–7)**
  - `std::atomic`, CAS loops, memory orders (`relaxed`, `acquire`/`release`, `seq_cst`)
  - Happens-before relations, Store Buffers, ABA problem
  - Projects: Spinlock, Ticket Lock, Atomic Counter benchmarks
- **Phase 3: Hardware Awareness (Weeks 8–10)**
  - Cache line mechanics (64-byte alignment), False Sharing, MESI protocol, NUMA
  - Thread pinning (`pthread_setaffinity_np`), `isolcpus`, huge pages
  - Projects: Padded vs. Unpadded performance benchmarks
- **Phase 4: Lock-Free Structures (Weeks 11–14)**
  - Lock-free Single-Producer Single-Consumer (SPSC) ring buffer
  - MPMC Queues, Memory reclamation (Hazard Pointers, Epoch-based)
  - Projects: Low-latency circular ring buffer
- **Phase 5: Capstone Application (Weeks 15+)**
  - Tooling: ThreadSanitizer (TSan), Valgrind/Helgrind, `perf`, Google Benchmark
  - Capstone: Market Data Feed Handler & Pinned L2/L3 Order Book pipeline measuring tail latencies ($p50$, $p99$, $p99.9$).

---

## 📁 Repository Structure

```text
├── notes/                 # Concepts, assembly breakdowns, interview questions
├── phase1-fundamentals/   # Thread pool, blocking queue, parallel algorithms
├── phase2-atomics/        # Spinlocks, ticket locks, memory ordering tests
├── phase3-hardware/       # False sharing benchmarks, thread pinning
├── phase4-lockfree/       # Lock-free SPSC / MPMC ring buffers
└── phase5-capstone/       # Market data feed handler + order book pipeline
```
