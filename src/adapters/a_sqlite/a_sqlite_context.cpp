#include <a_sqlite_context.h>

#include <sqlite3.h>

namespace a_sqlite {

Context::Context(sqlite3_context* context) : m_context(context) {}

}  // namespace a_sqlite
