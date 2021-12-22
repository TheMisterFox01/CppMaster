# CMakeList.txt: проект CMake для TreeXML; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("TreeXML")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (TreeXML "main.cpp"  "XMLReader.h" "XMLReader.cpp" "Tree.h" "Tree.cpp" "XMLTree.cpp")
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
