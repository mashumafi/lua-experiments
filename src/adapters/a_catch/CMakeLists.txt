add_library(a_catch catch2.m.cpp)
target_link_libraries(a_catch PUBLIC Catch2)
include(Compile)
target_compile(a_catch)