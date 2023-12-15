cmake_minimum_required(VERSION 3.12)
project(threads)

set(CMAKE_CXX_STANDARD 11)

# Adăugați executabilul și fișierele sursă
add_executable(threads threads.cpp)

# Găsește pachetele necesare pentru C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
