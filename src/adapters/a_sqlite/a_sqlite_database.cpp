#include <a_sqlite_database.h>

#include <sqlite3.h>

namespace a_sqlite {

Database::Database(std::string_view filename) {
  sqlite3* db;
  sqlite3_open(filename.data(), &db);
  m_db = std::shared_ptr<sqlite3>(db, [](sqlite3* db) { sqlite3_close(db); });
}

const std::shared_ptr<sqlite3>& Database::getHandle() const {
  return m_db;
}

}  // namespace a_sqlite
