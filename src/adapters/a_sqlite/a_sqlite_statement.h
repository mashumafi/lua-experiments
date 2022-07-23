#ifndef A_SQLITE_STATEMENT_H
#define A_SQLITE_STATEMENT_H

#include <a_sqlite_database.h>

#include <memory>
#include <string_view>

struct sqlite3_stmt;

namespace a_sqlite {

class Statement {
 public:
  Statement(Database& db, std::string_view sql, std::string_view& tail);

  int bindDouble(int index, double val);

  int step();

  double columnDouble(int col);

 private:
  std::shared_ptr<sqlite3_stmt> m_stmt;
};

}  // namespace a_sqlite

#endif
