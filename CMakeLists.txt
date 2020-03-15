cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project (DeCasteljau)
add_executable(DeCasteljau bezier.cpp  main.cpp  output.cpp)

