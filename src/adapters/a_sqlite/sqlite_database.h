#ifndef SQLITE_DATABASE_INCLUDED
#define SQLITE_DATABASE_INCLUDED

#include "sqlite_statement.h"

#include <string_view>

struct sqlite3;

namespace sqlite
{

class Database
{
    sqlite3 *m_db;

public:
    Database();
    Database(std::string_view filename);
    virtual ~Database();

    int exec(std::string_view sql);

    Statement prepare(std::string_view sql);
    Statement prepare(std::string_view sql, std::string_view &tail);

    bool valid() const;
    operator bool() const
    {
        return valid();
    }

    int errcode();
    std::string_view errmsg();
};

} // namespace sqlite

#endif