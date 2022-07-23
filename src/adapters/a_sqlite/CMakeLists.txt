add_library(a_sqlite a_sqlite_database.cpp a_sqlite_statement.cpp)
target_include_directories(a_sqlite PUBLIC .)
target_link_libraries(a_sqlite PRIVATE sqlite dl pthread)
target_compile_features(a_sqlite PUBLIC cxx_std_17)

add_executable(a_sqlite_test
    a_sqlite_database.t.cpp
)
target_link_libraries(a_sqlite_test PRIVATE a_sqlite a_catch sqlite)
add_test(a_sqlite_test a_sqlite_test)
