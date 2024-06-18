#ifndef A_SQLITE_VALUE_H
#define A_SQLITE_VALUE_H

#include <string_view>

struct sqlite3_value;

namespace a_sqlite {

class Value {
 public:
  Value(sqlite3_value* value = nullptr);

 private:
  sqlite3_value* m_value;
};

}  // namespace a_sqlite

#endif
