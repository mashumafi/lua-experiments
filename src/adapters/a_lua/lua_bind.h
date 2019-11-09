#ifndef LUA_BIND_INCLUDED
#define LUA_BIND_INCLUDED

#include "lua_state.h"
#include "lua_function_traits.h"

#include <functional>
#include <tuple>

namespace lua
{

template <class T>
bool is(State &state, int idx);

template <class T>
T argument(State &state, int idx);

template <class T>
bool argument(State &state, int idx, T &value);

template <class T>
class Iterator
{
    State &m_state;
    int m_idx;

public:
    Iterator(State &state, int idx)
        : m_state(state), m_idx(idx)
    {
    }

    bool operator!=(Iterator<T> other)
    {
        return m_idx != other.m_idx;
    }

    int operator++()
    {
        return m_idx++;
    }

    T operator*()
    {
        return argument<T>(m_state, m_idx);
    }
};

template <class T>
class Variadic
{
    State *m_state;
    int m_idx;

public:
    Variadic()
    {
    }

    Variadic(State &state, int idx)
        : m_state(&state), m_idx(idx)
    {
    }

    Variadic<T> &operator=(const Variadic<T> &other)
    {
        m_state = other.m_state;
        m_idx = other.m_idx;
        return *this;
    }

    T operator[](int idx) const
    {
        return argument<T>(*m_state, m_idx + idx);
    }

    Iterator<T> begin() const
    {
        return Iterator<T>(*m_state, m_idx);
    }

    Iterator<T> end() const
    {
        return Iterator<T>(*m_state, m_state->gettop() + 1);
    }

    size_t size() const
    {
        return m_state->gettop() - m_idx;
    }
};

template <>
bool is<double>(State &state, int idx)
{
    return state.isnumber(idx);
}

template <>
double argument(State &state, int idx)
{
    return state.tonumber(idx);
}

template <>
bool argument(State &state, int idx, double &value)
{
    if (is<double>(state, idx))
    {
        value = state.tonumber(idx);
        return true;
    }
    return false;
}

template <>
bool argument(State &state, int idx, Variadic<double> &value)
{
    int n = state.gettop();
    for (int i = idx; i < n; i++)
    {
        if (!is<double>(state, i))
        {
            return false;
        }
    }
    value = Variadic<double>(state, idx);
    return true;
}

int result(State &state, const double &value)
{
    state.push(value);
    return 1;
}

template <std::size_t I = 0, class... Tp>
typename std::enable_if<I == sizeof...(Tp), int>::type result(State &, const std::tuple<Tp...> &)
{
    return 0;
}

template <std::size_t I = 0, class... Tp>
    typename std::enable_if < I<sizeof...(Tp), int>::type result(State &state, const std::tuple<Tp...> &t)
{
    state.push(std::get<I>(t));
    return result<I + 1, Tp...>(state, t) + 1;
}

template <std::size_t I = 0, class... Tp>
typename std::enable_if<I == sizeof...(Tp), bool>::type set(State &, std::tuple<Tp...> &)
{
    return true;
}

template <std::size_t I = 0, class... Tp>
    typename std::enable_if < I<sizeof...(Tp), bool>::type set(State &state, std::tuple<Tp...> &t)
{
    using type = typename std::tuple_element<I, std::tuple<Tp...>>::type;
    bool success = argument<type>(state, I + 1, std::get<I>(t));
    if (success)
    {
        return set<I + 1, Tp...>(state, t);
    }
    return false;
}

template <typename F>
class Bind
{
    F m_func;

public:
    Bind(F func) : m_func(func)
    {
    }

    int operator()(State &state)
    {
        function_traits<F>::arguments args;
        if (set(state, args))
        {
            return result(state, std::apply(m_func, args));
        }
        return 0;
    }
};

} // namespace lua

#endif