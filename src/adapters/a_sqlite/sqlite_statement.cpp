#include "sqlite_statement.h"

#include <iostream>

extern "C"
{
#include <sqlite3.h>
}

namespace sqlite
{

int getstatus()
{
    return SQLITE_DONE;
}
int getstatus(sqlite3_stmt *stmt)
{
    return sqlite3_step(stmt);
}

template <>
std::string_view column(sqlite3_stmt *stmt, int col)
{
    return reinterpret_cast<std::string_view::const_pointer>(sqlite3_column_text(stmt, col));
}

template <>
std::wstring_view column(sqlite3_stmt *stmt, int col)
{
    return static_cast<std::wstring_view::const_pointer>(sqlite3_column_text16(stmt, col));
}

template <>
int column(sqlite3_stmt *stmt, int col)
{
    return sqlite3_column_int(stmt, col);
}

Statement::Statement(sqlite3 *db, std::string_view sql) : m_stmt(nullptr)
{
    int rc = sqlite3_prepare_v2(db, sql.data(), static_cast<int>(sql.size()), &m_stmt, nullptr);
    if (rc != 0)
    {
        m_stmt = nullptr;
    }
}

Statement::Statement(sqlite3 *db, std::string_view sql, std::string_view &tail) : m_stmt(nullptr)
{
    const char *ptail;
    int rc = sqlite3_prepare_v2(db, sql.data(), static_cast<int>(sql.size()), &m_stmt, &ptail);
    if (rc != 0)
    {
        m_stmt = nullptr;
    }
    else
    {
        tail = ptail;
    }
}

Statement::~Statement()
{
    sqlite3_finalize(m_stmt);
}

bool Statement::valid() const
{
    return m_stmt;
}

int Statement::bind(int idx, int val)
{
    return sqlite3_bind_int(m_stmt, idx, val);
}

int Statement::column_int(int col)
{
    return sqlite3_column_int(m_stmt, col);
}

std::string_view Statement::column_text(int col)
{
    return static_cast<std::string_view::const_pointer>(sqlite3_column_text16(m_stmt, col));
}

} // namespace sqlite