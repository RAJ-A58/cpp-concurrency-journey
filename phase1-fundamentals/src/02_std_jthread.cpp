#include<chrono>
#include<thread>
#include<stop_token>
#include<iostream>

using namespace std;

void simple_worker(){
    cout << "[Worker] Starting work (sleeping for 100ms)...\n";
    this_thread::sleep_for(100ms);
    cout << "[Worker] Finished work!\n";
}

void stoppable_worker(std::stop_token st, int id) {
    cout << "[Worker " << id << "] Started.\n";
    int count = 0;
    while (!st.stop_requested()) {
        this_thread::sleep_for(50ms);
        ++count;
    }
    cout << "[Worker " << id << "] Stop received after " << count << " iterations. Exiting cleanly.\n";
}

int main(){
    cout << "[Main] Entering inner scope block {\n";
    
    {
        std::jthread t1(simple_worker);
        cout << "[Main] Reached end of block. ~jthread() is about to run...\n";
        // No t1.join() called!
    } // <-- t1 goes out of scope here. Its destructor automatically calls t1.join(),
      // blocking main() right at this closing brace until simple_worker() finishes.

    cout << "[Main] Exited block }. This prints ONLY after t1 has completely finished!\n";

    // 2. Auto-injected std::stop_token (Cooperative Interruption)
    // If the worker accepts std::stop_token as the first argument, jthread automatically
    // injects it. When jthread destructs, it calls request_stop() before join().
    {
        cout << "\n--- Pattern 2: Auto-injected stop_token ---\n";
        jthread t2(stoppable_worker, 42); // pass 42, but NOT the stop_token

        this_thread::sleep_for(160ms);    // let worker loop a few times
        cout << "[Main] Exiting block for t2 now...\n";
    } // ~jthread(): calls request_stop() -> calls join()

    cout << "[Main] t2 stopped and joined cleanly.\n";

    return 0;
}