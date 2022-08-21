#include <catch2/catch_all.hpp>

#include <a_sqlite_database.h>
#include <a_sqlite_statement.h>

#include <sqlite3.h>

TEST_CASE("Create a memory database", "[a_sqlite_database]") {
  a_sqlite::Database db(":memory:");
}

TEST_CASE("Insert and select data", "[a_sqlite_database]") {
  a_sqlite::Database db(std::string_view(":memory:"));
  std::string_view tail;

  a_sqlite::Statement stmtCreateTable(db, "CREATE TABLE demo (col1 double);",
                                      tail);
  REQUIRE(tail.empty());
  REQUIRE(stmtCreateTable.step() == SQLITE_DONE);

  a_sqlite::Statement stmtInsertRow(db, "INSERT INTO demo VALUES (?);", tail);
  REQUIRE(tail.empty());
  REQUIRE(stmtInsertRow.bind(1, 1.25) == SQLITE_OK);
  REQUIRE(stmtInsertRow.step() == SQLITE_DONE);

  a_sqlite::Statement stmtSelect(db, "select col1 from demo;", tail);
  REQUIRE(tail.empty());
  REQUIRE(stmtSelect.step() == SQLITE_ROW);
  REQUIRE(stmtSelect.columnDouble(0) == 1.25);
  REQUIRE(stmtSelect.step() == SQLITE_DONE);
}

TEST_CASE("Read and write CSV with header", "[a_sqlite_database]") {
  a_sqlite::Database db(std::string_view(":memory:"));
  std::string_view tail;
}
