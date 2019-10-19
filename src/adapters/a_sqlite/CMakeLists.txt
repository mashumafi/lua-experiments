add_library(a_sqlite sqlite_database.cpp
                     sqlite_statement.cpp)
target_include_directories(a_sqlite PUBLIC .)
target_link_libraries(a_sqlite PRIVATE sqlite3)
set_target_properties(a_sqlite PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)