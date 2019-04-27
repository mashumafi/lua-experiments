cmake_minimum_required(VERSION 3.14)

project(cpp17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

enable_testing()

add_subdirectory(adapters)
add_subdirectory(standalones)
