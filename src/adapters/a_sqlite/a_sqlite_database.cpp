#include <a_sqlite_database.h>

#include <sqlite3.h>

namespace a_sqlite {

namespace {

struct FunctionImpl : public Function {
  virtual void operator()(Context& context,
                          size_t argc,
                          Value* values) override {}
};

void xfunction(sqlite3_context* context, int argc, sqlite3_value** args) {
  FunctionImpl f;
  Context ctx(context);
  Value values[10];
  f(ctx, argc, values);
}

void xdestroy(void*) {}

}  // namespace

TextRep::TextRep() {
  setUtf();
  setDeterministic();
}

TextRep& TextRep::setText16le() {
  m_value |= SQLITE_UTF16LE;
  return *this;
}

TextRep& TextRep::setText16be() {
  m_value |= SQLITE_UTF16BE;
  return *this;
}

TextRep& TextRep::setText16() {
  m_value |= SQLITE_UTF16;
  return *this;
}

TextRep& TextRep::setUtf() {
  m_value |= SQLITE_UTF8;
  return *this;
}

TextRep& TextRep::setDeterministic() {
  m_value |= SQLITE_DETERMINISTIC;
  return *this;
}

TextRep& TextRep::setDirectOnly() {
  m_value |= SQLITE_DIRECTONLY;
  return *this;
}

TextRep& TextRep::reset() {
  m_value = 0;
  return *this;
}

int TextRep::value() const {
  return m_value;
}

Database::Database(std::string_view filename) {
  sqlite3* db;
  sqlite3_open(filename.data(), &db);
  m_db = std::shared_ptr<sqlite3>(db, [](sqlite3* db) { sqlite3_close(db); });
}

int Database::createFunction(std::string_view name,
                             const TextRep& textRep,
                             const Function& xFunc) {
  return sqlite3_create_function_v2(m_db.get(), name.data(), textRep.value(),
                                    -1, NULL, &xfunction, NULL, NULL,
                                    &xdestroy);
}

int Database::createFunction(std::string_view name,
                             const TextRep& textRep,
                             const Function& xStep,
                             const Function& xFinal) {
  return sqlite3_create_function_v2(m_db.get(), name.data(), textRep.value(),
                                    -1, NULL, &xfunction, NULL, NULL,
                                    &xdestroy);
}

const std::shared_ptr<sqlite3>& Database::getHandle() const {
  return m_db;
}

}  // namespace a_sqlite
