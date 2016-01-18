cmake_minimum_required(VERSION 2.8)

project(better_rev_comp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

include_directories(inc)

file(
  GLOB_RECURSE
  src_files
  src/*
  )

add_executable(
  better_rev_comp
  ${src_files}
  )











