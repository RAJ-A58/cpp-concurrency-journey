# Thread Creation, Parameter Passing & Lifetime Management

Notes based on **Chapter 2 of *C++ Concurrency in Action*** & C++20 standard additions.

---

## 1. How `std::thread` Handles Arguments (Decay by Default)

The `std::thread` constructor evaluates its arguments by decaying them (`std::decay_t`) and copying or moving them into internal thread storage before the new thread starts.

### Passing by Value
```cpp
void print(std::string s, int count);
std::thread t(print, "Hello", 3); // "Hello" is copied into an internal std::string
```

### Passing by Reference (`std::ref`)
If a thread function expects a non-const reference (`T&`), passing a variable directly will fail to compile because the constructor tries to pass an rvalue copy into a non-const lvalue reference.
```cpp
void increment(int& num);

int val = 5;
// std::thread t(increment, val);         // COMPILE ERROR!
std::thread t(increment, std::ref(val));  // OK: wrapped in std::reference_wrapper
t.join();
```

> **Crucial Lifetime Rule:** When passing variables by reference or pointer across a thread boundary, the caller thread's stack or object **must outlive the thread's execution**. If the thread is detached (`t.detach()`) or joins too late, it causes **Use-After-Free (Undefined Behavior)**.

---

## 2. Invoking Member Functions

To invoke a class member function inside a thread, pass:
1. Pointer to member function (`&Class::Method`)
2. Pointer or reference to the instance (`&object` or `std::ref(object)`)
3. Function arguments

```cpp
class TaskRunner {
public:
    void execute(int delta);
};

TaskRunner runner;
std::thread t(&TaskRunner::execute, &runner, 10);
t.join();
```

---

## 3. Thread IDs (`std::thread::id`)

Every thread has a unique identifier of type `std::thread::id`:
* Current thread ID: `std::this_thread::get_id()`
* Spawned thread ID: `t.get_id()`
* If a `std::thread` object does not represent an active thread of execution (default constructed, moved from, or joined), its ID equals `std::thread::id()` (the default/null ID).

---

## 4. `std::thread` vs `std::jthread` Summary

| Feature | `std::thread` (C++11) | `std::jthread` (C++20) |
|---|---|---|
| Destructor without `join()` | Calls `std::terminate()` (Crashes) | Automatically calls `request_stop()` + `join()` |
| Cooperative cancellation | None (manual flags needed) | Built-in `std::stop_token` support |
| Move-only semantics | Yes | Yes |
