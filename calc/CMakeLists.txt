cmake_minimum_required (VERSION 3.8)

project ("calc")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
add_executable (calc "calc.h" "calc.cpp" "main.cpp" "scanner.h" "token.h" "scanner.cpp" "parser.h" "parser.cpp" "evaluator.h" "evaluator.cpp" "plugin_loader.h" "plugin_loader.cpp")

# Example libraries.
add_subdirectory(trigonometry)
add_subdirectory(pow)