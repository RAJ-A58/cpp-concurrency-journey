cmake_minimum_required(VERSION 3.20)
project(Cpp_Concurrency LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler Warning Flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
    )
endif()

# ThreadSanitizer option: cmake -B build -DENABLE_TSAN=ON
option(ENABLE_TSAN "Enable ThreadSanitizer (TSan)" OFF)
if(ENABLE_TSAN)
    message(STATUS "ThreadSanitizer (TSan) ENABLED")
    add_compile_options(-fsanitize=thread -g -O1)
    add_link_options(-fsanitize=thread)
endif()

# AddressSanitizer option: cmake -B build -DENABLE_ASAN=ON
option(ENABLE_ASAN "Enable AddressSanitizer (ASan)" OFF)
if(ENABLE_ASAN)
    message(STATUS "AddressSanitizer (ASan) ENABLED")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g -O1)
    add_link_options(-fsanitize=address)
endif()

# Dependencies
find_package(Threads REQUIRED)
find_package(benchmark QUIET)

# Subdirectories
add_subdirectory(phase1-fundamentals)
