# CMakeList.txt : CMake project for deque, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(Deque)

# Add source to this project's executable.
add_executable (Deque "deque.cpp" "deque.h" "MemoryHeapStrategy.h")
