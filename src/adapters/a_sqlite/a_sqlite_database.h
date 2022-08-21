#ifndef A_SQLITE_DATABASE_H
#define A_SQLITE_DATABASE_H

#include <a_sqlite_context.h>
#include <a_sqlite_value.h>

#include <functional>
#include <memory>
#include <string_view>

struct sqlite3;

namespace a_sqlite {

struct Function {
  virtual int nArg() const { return -1; }

  virtual void operator()(Context& context, size_t argc, Value* values) = 0;
};

class TextRep {
 public:
  TextRep();

  TextRep& setText16le();
  TextRep& setText16be();
  TextRep& setText16();
  TextRep& setUtf();

  TextRep& setDeterministic();

  TextRep& setDirectOnly();

  TextRep& reset();

  int value() const;

 private:
  int m_value;
};

class Statement;

class Database {
 public:
  Database(std::string_view filename);

  int createFunction(std::string_view name,
                     const TextRep& textRep,
                     const Function& xFunc);
  int createFunction(std::string_view name,
                     const TextRep& textRep,
                     const Function& xStep,
                     const Function& xFinal);

  const std::shared_ptr<sqlite3>& getHandle() const;

 private:
  std::shared_ptr<sqlite3> m_db;
};

}  // namespace a_sqlite

#endif
