#include <functional> // Provides std::ref() to pass variables by reference
#include <iostream>
#include <string>
#include <thread>

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

    return 0;
}
