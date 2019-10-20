add_library(a_sqlite sqlite_database.cpp
                     sqlite_statement.cpp)
target_include_directories(a_sqlite PUBLIC .)
target_link_libraries(a_sqlite PRIVATE sqlite)
include(Compile)
target_compile(a_sqlite)