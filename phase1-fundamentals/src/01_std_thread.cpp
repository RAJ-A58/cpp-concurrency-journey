#include <chrono>     // Provides std::chrono::milliseconds for sleep durations
#include <functional> // Provides std::ref() to pass variables by reference
#include <iostream>
#include <string>
#include <thread>
#include <utility>    // Provides std::swap for non-member swap

using namespace std;

// 1. Thread ID Inspection
// std::this_thread::get_id() returns a unique handle identifying the active thread context.
void work() {
    cout << "Worker running on thread id: " << this_thread::get_id() << "\n";
}

// 2. Passing Arguments by Value
// std::thread decays and copies/moves arguments into the newly created thread's storage.
void printMessage(string s, int count) {
    for (int i = 0; i < count; ++i) {
        cout << s << "\n";
    }
}

// 3. Passing Arguments by Reference
// std::thread decays arguments by default, so it cannot bind an lvalue to a non-const reference (int&).
// std::ref() creates a std::reference_wrapper to explicitly pass the reference across the thread boundary.
// Lifetime Warning: 'num' must outlive the thread execution (ensured here by t3.join()).
void increment(int& num) {
    num += 10;
    cout << "Value of num in increment func is: " << num << "\n";
}

// 4. Executing Member Functions on an Object Instance
class taskrunner {
public:
    int data = 0;

    void execute(int increment_by) {
        data += increment_by;
        cout << "Thread data updated to: " << data << "\n";
    }
};


//If the member function is marked static, it does not belong to any specific object instance (it has no this pointer). 
// You pass it just like a regular free function without needing an object instance:
class Logger {
public:
    static void log(const std::string& msg) {
        std::cout << "[LOG]: " << msg << '\n';
    }
};

int main() {
    taskrunner runner;

    // Pattern 1: Basic invocation
    thread t1(work);
    t1.join();
    cout << "Worker done\n";

    // Pattern 2: Passing parameters by value
    thread t2(printMessage, "Hello", 3);
    t2.join();

    // Pattern 3: Passing parameters by reference using std::ref
    int mynum = 5;
    thread t3(increment, ref(mynum));
    t3.join();
    cout << "In Main: " << mynum << "\n"; // Prints 15

    // Pattern 4: Invoking a member function on an object pointer
    // Syntax: &Class::Method, &instance, arguments...
    thread t4(&taskrunner::execute, &runner, 10);
    t4.join();
    cout << "Main sees runner.data as: " << runner.data << "\n"; // Prints 10

    // Capture 'runner' by reference and call the method normally
    //In modern C++, many developers prefer wrapping member function calls inside a lambda expression. 
    // It reads like a standard function call and makes how you capture the object 
    // (&runner by reference vs. runner by value) immediately obvious.
    std::thread t5([&runner]() {
        runner.execute(42);
    });

    t5.join();

    //for static method we do not pass the object Instance.
    std::thread t6(&Logger::log, "System started");
    t6.join();

    // 5. joinable()
    // Returns true if this object owns a live OS thread.
    // False after: default construction, join(), detach(), or move-from.
    // Always guard with joinable() before conditionally calling join()/detach()
    // — calling either on a non-joinable thread is undefined behaviour.
    {
        std::thread t7(work);
        std::cout << "t7 joinable before join: " << std::boolalpha << t7.joinable() << "\n";
        t7.join();
        std::cout << "t7 joinable after join:  " << std::boolalpha << t7.joinable() << "\n";
    }

    // 6. detach()
    // Severs the std::thread handle from the OS thread; the OS thread keeps
    // running independently ("fire-and-forget"). The handle becomes non-joinable.
    // Lifetime rule: a detached thread must never touch caller-scope variables —
    // pass data BY VALUE so the thread owns its own copy.
    // DANGER: std::thread t(fn, std::ref(local)); t.detach();
    //         → 'local' may be destroyed before the thread reads it (UB).
    {
        std::thread t8(printMessage, "Hello from detached thread", 1); // arg copied by value — safe
        if (t8.joinable()) t8.detach();
        std::cout << "t8 joinable after detach: " << std::boolalpha << t8.joinable() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // let detached thread finish
    }

    // 7. operator= (move-assignment) and swap()
    // std::thread is MOVE-ONLY — no copy constructor or copy-assignment.
    // Move-assignment transfers OS thread ownership; the source becomes non-joinable.
    // swap() / std::swap() exchanges which OS thread two handles manage.
    {
        std::thread t9(work);
        std::thread t10;                               // default-constructed → non-joinable
        std::cout << "Before move — t9 joinable: " << t9.joinable()
                  << "  t10 joinable: " << t10.joinable() << "\n";
        t10 = std::move(t9);                           // ownership: t9 → t10; t9 is now empty
        std::cout << "After move  — t9 joinable: " << t9.joinable()
                  << "  t10 joinable: " << t10.joinable() << "\n";
        t10.join();

        std::thread ta(work);
        std::thread tb(work);
        std::cout << "Before swap — ta id: " << ta.get_id() << "  tb id: " << tb.get_id() << "\n";
        ta.swap(tb);                                   // member swap; std::swap(ta, tb) is identical
        std::cout << "After swap  — ta id: " << ta.get_id() << "  tb id: " << tb.get_id() << "\n";
        ta.join();
        tb.join();
    }

    return 0;
}
