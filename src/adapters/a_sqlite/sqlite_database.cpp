#include "sqlite_database.h"

extern "C"
{
#include <sqlite3.h>
}

namespace sqlite
{

Database::Database() : Database(":memory:")
{
}

Database::Database(std::string_view filename) : m_db(nullptr)
{
    int rc = sqlite3_open(filename.data(), &m_db);
    if (rc != 0)
    {
        m_db = nullptr;
    }
}

Database::~Database()
{
    int rc = sqlite3_close(m_db);
}

int callback(void *, int, char **, char **)
{
    return SQLITE_OK;
}

int Database::exec(std::string_view sql)
{
    return sqlite3_exec(m_db, sql.data(), callback, nullptr, nullptr);
}

Statement Database::prepare(std::string_view sql)
{
    return Statement(m_db, sql);
}

Statement Database::prepare(std::string_view sql, std::string_view &tail)
{
    return Statement(m_db, sql, tail);
}

bool Database::valid() const
{
    return m_db;
}

int Database::errcode()
{
    return sqlite3_errcode(m_db);
}

std::string_view Database::errmsg()
{
    return sqlite3_errmsg(m_db);
}

} // namespace sqlite