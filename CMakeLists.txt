cmake_minimum_required(VERSION 3.14)

project(lua-experiments LANGUAGES C CXX VERSION 0.0.1)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
add_subdirectory(src)