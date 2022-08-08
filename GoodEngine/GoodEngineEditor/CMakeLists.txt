# CMakeList.txt: проект CMake для GoodEngine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("GoodEngineEditor")

set(EDITOR_PROJECT_NAME GoodEngineEditor)
# Добавьте источник в исполняемый файл этого проекта.
add_executable(${EDITOR_PROJECT_NAME}
	src/main.cpp
)

target_link_libraries(${EDITOR_PROJECT_NAME} GoodEngineCore)
target_compile_features(${EDITOR_PROJECT_NAME} PUBLIC cxx_std_20)

set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
