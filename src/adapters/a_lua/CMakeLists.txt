add_library(a_lua lua_state.cpp)
target_include_directories(a_lua PUBLIC .)
target_link_libraries(a_lua PRIVATE lua5)
set_target_properties(a_lua PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)