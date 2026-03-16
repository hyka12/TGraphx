cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

add_executable(MyProgram)

file(GLOB SOURCES "src/*.cpp")
target_sources(MyProgram PRIVATE ${SOURCES})

target_include_directories(MyProgram PRIVATE $(CMAKE_CURRENT_SOURCE_DIR)/include)

