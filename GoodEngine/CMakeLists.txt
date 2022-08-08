# CMakeList.txt: проект CMake для GoodEngine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("GoodEngine")

set(PROJECT_NAME GoodEngine)

add_subdirectory(GoodEngineCore)
add_subdirectory(GoodEngineEditor)

