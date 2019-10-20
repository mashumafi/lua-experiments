add_library(formula datum.cpp
                    lexer.cpp
                    parser.cpp
                    token.cpp
)
target_include_directories(formula PUBLIC .)
include(Compile)
target_compile(formula)

add_executable(formula_test datum.t.cpp
                            lexer.t.cpp
                            parser.t.cpp
                            token.t.cpp
)
target_link_libraries(formula_test PRIVATE a_catch formula)
target_compile(formula_test)
include(Catch)
catch_discover_tests(formula_test)