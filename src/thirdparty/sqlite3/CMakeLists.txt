include(FetchContent)

FetchContent_Declare(
  sqlite
  URL      https://www.sqlite.org/2019/sqlite-amalgamation-3300100.zip
  URL_HASH SHA1=ff9b4e140fe0764bc7bc802facf5ac164443f517
)

FetchContent_GetProperties(sqlite)
if(NOT sqlite_POPULATED)
    FetchContent_Populate(sqlite)
    add_library(sqlite3 ${sqlite_SOURCE_DIR}/sqlite3.c)
    target_include_directories(sqlite3 PUBLIC ${sqlite_SOURCE_DIR})
endif()
