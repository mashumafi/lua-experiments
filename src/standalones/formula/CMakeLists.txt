add_library(formula datum.cpp
                    lexer.cpp
                    parser.cpp
                    token.cpp
)
target_include_directories(formula PUBLIC .)
set_target_properties(formula PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_executable(formula_test datum.t.cpp
                            lexer.t.cpp
                            parser.t.cpp
                            token.t.cpp
)
target_link_libraries(formula_test PRIVATE a_catch formula)
set_target_properties(formula_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

include(Catch)
catch_discover_tests(formula_test)