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


set(IMGUI_INCLUDES
	../external/imgui/imgui.h
	../external/imgui/backends/imgui_impl_glfw.h
	../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
	../external/imgui/imgui.cpp
	../external/imgui/backends/imgui_impl_glfw.cpp
	../external/imgui/backends/imgui_impl_opengl3.cpp
	../external/imgui/imgui_demo.cpp
	../external/imgui/imgui_draw.cpp
	../external/imgui/imgui_widgets.cpp
	../external/imgui/imgui_tables.cpp
)
add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)

target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)