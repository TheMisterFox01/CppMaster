cmake_minimum_required (VERSION 3.8)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build/plugins)

project ("trig")
add_library(trig SHARED "trig.cpp")
