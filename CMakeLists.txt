cmake_minimum_required(VERSION 3.20)
project(Atmos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "Configuration types" FORCE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/GLFW)

# Include directories
set(INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/vendor/spdlog/include"
    "${CMAKE_SOURCE_DIR}/vendor/GLFW/include"
    "${CMAKE_SOURCE_DIR}/vendor/glad/include"
    "${CMAKE_SOURCE_DIR}/vendor/imgui"
    "${CMAKE_SOURCE_DIR}/vendor/glm"
    "${CMAKE_SOURCE_DIR}/vendor/stb_image"
    "${CMAKE_SOURCE_DIR}/vendor/entt/include"
)

# Source files
file(GLOB_RECURSE ATMOS_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/stb_image/*.h"
    "${CMAKE_SOURCE_DIR}/vendor/stb_image/*.cpp"
    "${CMAKE_SOURCE_DIR}/vendor/glm/glm/*.hpp"
    "${CMAKE_SOURCE_DIR}/vendor/glm/glm/*.inl"
)

#Include glad
add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)

#Include imgui
set(IMGUI_DIR vendor/imgui)
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

add_executable(Atmos ${ATMOS_SOURCES})

target_compile_definitions(Atmos PRIVATE
    _CRT_SECURE_NO_WARNINGS
    GLFW_INCLUDE_NONE
)

target_include_directories(Atmos PRIVATE ${INCLUDE_DIRS})

#Link libraries
find_library(OPENGL_LIBRARY NAMES opengl32)
target_link_libraries(Atmos PRIVATE
    glfw
    glad
    imgui
    ${OPENGL_LIBRARY}
)

target_compile_options(Atmos PRIVATE
    $<$<CONFIG:Debug>:/utf-8>
    $<$<CONFIG:Release>:/utf-8 /O2>
    $<$<CONFIG:Dist>:/utf-8 /O2>
)

# Enable parallel compilation
if(MSVC)
    target_compile_options(Atmos PRIVATE /MP)
endif()

#PCH
target_precompile_headers(Atmos PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h>")