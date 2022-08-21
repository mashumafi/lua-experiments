#ifndef A_SQLITE_CONTEXT_H
#define A_SQLITE_CONTEXT_H

#include <string_view>

struct sqlite3_context;

namespace a_sqlite {

class Context {
 public:
  Context(sqlite3_context* context);

 private:
  sqlite3_context* m_context;
};

}  // namespace a_sqlite

#endif
