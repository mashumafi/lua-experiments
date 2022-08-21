#include <a_sqlite_value.h>

#include <sqlite3.h>

namespace a_sqlite {

Value::Value(sqlite3_value* value) : m_value(value) {}

}  // namespace a_sqlite
