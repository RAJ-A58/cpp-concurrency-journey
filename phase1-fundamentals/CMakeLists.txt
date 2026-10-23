add_executable(01_thread_basics src/01_thread_basics.cpp)
target_link_libraries(01_thread_basics PRIVATE Threads::Threads)

add_executable(thread_program src/thread_program.cpp)
target_link_libraries(thread_program PRIVATE Threads::Threads)

