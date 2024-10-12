cmake_minimum_required(VERSION 3.30)
project(Zyn VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

set(PCH_FILE "src/zynpch.h")

file(GLOB_RECURSE HEADERS "src/**.h")
file(GLOB_RECURSE SOURCES "src/**.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_FILE})