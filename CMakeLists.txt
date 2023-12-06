cmake_minimum_required(VERSION 3.27.9)

project("Advent of Code")

add_executable(a.out  day4.cpp)

target_compile_features(a.out PRIVATE cxx_std_11)

