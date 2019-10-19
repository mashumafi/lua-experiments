add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE a_lua a_sqlite)
set_target_properties(demo PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)