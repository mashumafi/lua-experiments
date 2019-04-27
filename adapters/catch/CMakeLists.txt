add_library(catch src/catch.m.cpp)
target_link_libraries(catch PUBLIC CONAN_PKG::Catch2)