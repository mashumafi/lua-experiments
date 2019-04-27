add_library(formula src/datum.cpp
                    src/lexer.cpp
                    src/parser.cpp
                    src/token.cpp
)
target_include_directories(formula PUBLIC include)
set_target_properties(formula PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_executable(formula_test test/datum.t.cpp
                            test/lexer.t.cpp
                            test/parser.t.cpp
                            test/token.t.cpp
)
target_link_libraries(formula_test PRIVATE catch formula)
set_target_properties(formula_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_test(formula_test formula_test)