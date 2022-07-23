#ifndef A_SQLITE_DATABASE_H
#define A_SQLITE_DATABASE_H

#include <memory>
#include <string_view>

struct sqlite3;

namespace a_sqlite {

class Statement;

class Database {
 public:
  Database(std::string_view filename);

  const std::shared_ptr<sqlite3>& getHandle() const;

 private:
  std::shared_ptr<sqlite3> m_db;
};

}  // namespace a_sqlite

#endif
