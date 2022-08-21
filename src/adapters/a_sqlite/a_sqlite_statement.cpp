#include <a_sqlite_statement.h>

#include <stdexcept>

#include <sqlite3.h>

namespace a_sqlite {

Statement::Statement(Database& db,
                     std::string_view sql,
                     std::string_view& tail) {
  sqlite3_stmt* stmt;
  const char* pTail;
  int result = sqlite3_prepare_v2(db.getHandle().get(), sql.data(), sql.size(),
                                  &stmt, &pTail);
  if (result != SQLITE_OK) {
    throw std::runtime_error("Invalid sql");
  }
  tail = pTail;
  m_stmt = std::shared_ptr<sqlite3_stmt>(
      stmt, [](sqlite3_stmt* stmt) { sqlite3_finalize(stmt); });
}

int Statement::bind(int index, double val) {
  return sqlite3_bind_double(m_stmt.get(), index, val);
}

int Statement::step() {
  return sqlite3_step(m_stmt.get());
}

double Statement::columnDouble(int col) {
  return sqlite3_column_double(m_stmt.get(), col);
}

}  // namespace a_sqlite
