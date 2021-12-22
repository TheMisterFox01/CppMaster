# CMakeList.txt: проект CMake для reverse_list; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("reverse_list")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (reverse_list  "ReverseList.h"  "main.cpp" )

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
