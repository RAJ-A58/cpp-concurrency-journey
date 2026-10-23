add_executable(01_std_thread src/01_std_thread.cpp)
target_link_libraries(01_std_thread PRIVATE Threads::Threads)

add_executable(02_std_jthread src/02_std_jthread.cpp)
target_link_libraries(02_std_jthread PRIVATE Threads::Threads)

