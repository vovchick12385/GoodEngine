# CMakeList.txt: проект CMake для GoodEngine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("GoodEngineCore")

set(ENGINE_PROJECT_NAME GoodEngineCore)
set(ENGINE_PUBLIC_INCLUDES
	includes/GoodEngineCore/Application.h
	includes/GoodEngineCore/Log.h
	includes/GoodEngineCore/Event.h
)

set(ENGINE_PRIVATE_INCLUDES
	includes/GoodEngineCore/Window.h
)

set(ENGINE_PRIVATE_SOURCES
	src/GoodEngineCore/Application.cpp
	src/GoodEngineCore/Log.cpp
	src/GoodEngineCore/Window.cpp
	src/GoodEngineCore/Event.cpp
)

add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
	${ENGINE_PRIVATE_INCLUDES}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE includes)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)