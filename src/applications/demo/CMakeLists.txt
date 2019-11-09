add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE a_lua a_sqlite allocator logger main singleton)
include(Compile)
target_compile(demo)