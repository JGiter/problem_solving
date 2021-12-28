cmake_minimum_required(VERSION 3.22)

add_executable(absolute_permutation absolute_permutation.cpp)

target_compile_features(absolute_permutation PRIVATE cxx_std_17)

configure_file(data data)
