add_library(formula datum.h
                    datum.cpp
                    lexer.h
                    lexer.cpp
                    parser.h
                    parser.cpp
                    token.h
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
target_link_libraries(formula_test PRIVATE catch2 formula)
set_target_properties(formula_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_test(formula_test formula_test)