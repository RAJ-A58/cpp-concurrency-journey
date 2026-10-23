#include <chrono>
#include <iostream>
#include <stop_token>
#include <string>
#include <thread>
#include <vector>

void worker_with_stop_token(std::stop_token st, int id) {
    std::cout << "[Worker " << id << "] Started on thread ID: " 
              << std::this_thread::get_id() << '\n';

    int counter = 0;
    // Check stop_requested() periodically (cooperative interruption)
    while (!st.stop_requested()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        ++counter;
    }

    std::cout << "[Worker " << id << "] Stop requested after " 
              << counter << " iterations. Cleaning up and exiting cleanly.\n";
}

int main() {
    std::cout << "=====================================================\n";
    std::cout << "  Topic 1.1: Thread Lifecycle & C++20 std::jthread\n";
    std::cout << "=====================================================\n\n";

    // 1. Hardware Concurrency
    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "[Hardware] Logical cores reported by OS: " << cores << "\n\n";

    // 2. The Power of C++20 std::jthread
    // Unlike std::thread, std::jthread:
    //  a) Automatically requests stop and joins in its destructor (RAII)
    //  b) Can pass a std::stop_token directly to the thread function
    std::cout << "--- 1. Launching std::jthread with cooperative stop token ---\n";
    {
        // Spawning 3 jthreads inside a scoped block
        std::vector<std::jthread> workers;
        workers.reserve(3);

        for (int i = 1; i <= 3; ++i) {
            workers.emplace_back(worker_with_stop_token, i);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(180));
        std::cout << "\n[Main] Exiting scoped block now (destructors will fire)...\n";
        // Destructors of workers are called here:
        // Automatically: request_stop() -> join()
    }
    std::cout << "[Main] All workers joined safely without manual join() calls!\n\n";

    // 3. Explicit Stop Request
    std::cout << "--- 2. Explicit request_stop() Demo ---\n";
    {
        std::jthread explicit_worker(worker_with_stop_token, 99);
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
        
        std::cout << "[Main] Requesting stop explicitly...\n";
        explicit_worker.request_stop();

        // Check if stop was requested
        if (explicit_worker.get_stop_token().stop_requested()) {
            std::cout << "[Main] Verified: stop_requested is true.\n";
        }
    }

    std::cout << "\n--- Demo Completed Successfully ---\n";
    return 0;
}
