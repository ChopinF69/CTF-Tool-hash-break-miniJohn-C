cmake_minimum_required(VERSION 3.10)
project(miniJohn)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(test)
include_directories(include)

add_executable(miniJohn dictionary.cpp
        include/include_hashes.h
        )
target_link_libraries(miniJohn pthread)

add_executable(tests test/testing.cpp
        include/include_hashes.h
        )

add_executable(bruteForce brute.cpp
        include/include_hashes.h
        )