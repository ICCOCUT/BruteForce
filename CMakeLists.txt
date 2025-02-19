cmake_minimum_required(VERSION 3.30)
project(BruteForce C)

set(CMAKE_C_STANDARD 23)
find_package(OpenMP REQUIRED)

include_directories(include)

add_executable(BruteForce main.c src/brute_force.c src/key_generator.c)

target_link_libraries(BruteForce OpenMP::OpenMP_C)