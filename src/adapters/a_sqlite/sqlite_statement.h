#ifndef SQLITE_STATEMENT_INCLUDED
#define SQLITE_STATEMENT_INCLUDED

#include <string_view>
#include <tuple>

struct sqlite3;
struct sqlite3_stmt;

namespace sqlite
{

int getstatus();
int getstatus(sqlite3_stmt *stmt);

template <class T>
T column(sqlite3_stmt *stmt, int col);

template <std::size_t I = 0, class... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type columns(sqlite3_stmt *stmt, std::tuple<Tp...> &t)
{
}

template <std::size_t I = 0, class... Tp>
    inline typename std::enable_if < I<sizeof...(Tp), void>::type columns(sqlite3_stmt *stmt, std::tuple<Tp...> &t)
{
    using type = typename std::tuple_element<I, std::tuple<Tp...>>::type;
    std::get<I>(t) = column<type>(stmt, I);
    columns<I + 1, Tp...>(stmt, t);
}

template <class... T>
class Row
{
    sqlite3_stmt *m_stmt;
    int m_status;

public:
    Row() : m_status(getstatus())
    {
    }
    Row(sqlite3_stmt *stmt) : m_stmt(stmt), m_status(getstatus(stmt))
    {
    }

    bool operator!=(Row<T...> other)
    {
        return m_status != other.m_status;
    }

    void operator++()
    {
        m_status = getstatus(m_stmt);
    }

    std::tuple<T...> operator*()
    {
        std::tuple<T...> cols;
        columns(m_stmt, cols);
        return cols;
    }
};

template <class... T>
class Rows
{
    sqlite3_stmt *m_stmt;

public:
    Rows(sqlite3_stmt *stmt) : m_stmt(stmt)
    {
    }

    Row<T...> begin() const
    {
        return Row<T...>(m_stmt);
    }

    Row<T...> end() const
    {
        return Row<T...>();
    }

    operator bool()
    {
        return begin() != end();
    }
};

class Statement
{
    sqlite3_stmt *m_stmt;

public:
    Statement(sqlite3 *db, std::string_view sql);
    Statement(sqlite3 *db, std::string_view sql, std::string_view &tail);
    virtual ~Statement();

    bool valid() const;
    operator bool() const
    {
        return valid();
    }

    int bind(int idx, int val);

    int column_int(int col);
    std::string_view column_text(int col);

    template <class... T>
    Rows<T...> step()
    {
        return Rows<T...>(m_stmt);
    }
};

} // namespace sqlite

#endif