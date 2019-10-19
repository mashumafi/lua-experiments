#ifndef LUA_BIND_INCLUDED
#define LUA_BIND_INCLUDED

#include "lua_state.h"

#include <functional>
#include <tuple>

namespace lua
{

template <class T>
inline bool is(State &state, int idx);

template <class T>
inline T argument(State &state, int idx);

template <class T>
inline bool argument(State &state, int idx, T &value);

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
inline bool is<double>(State &state, int idx)
{
    return state.isnumber(idx);
}

template <>
inline double argument(State &state, int idx)
{
    return state.tonumber(idx);
}

template <>
inline bool argument(State &state, int idx, double &value)
{
    if (is<double>(state, idx))
    {
        value = state.tonumber(idx);
        return true;
    }
    return false;
}

template <>
inline bool argument(State &state, int idx, Variadic<double> &value)
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

inline int result(State &state, const double &value)
{
    state.push(value);
    return 1;
}

template <std::size_t I = 0, class... Tp>
inline typename std::enable_if<I == sizeof...(Tp), int>::type result(State &state, const std::tuple<Tp...> &t)
{
    return 0;
}

template <std::size_t I = 0, class... Tp>
    inline typename std::enable_if < I<sizeof...(Tp), int>::type result(State &state, const std::tuple<Tp...> &t)
{
    state.push(std::get<I>(t));
    return result<I + 1, Tp...>(state, t) + 1;
}

template <std::size_t I = 0, class... Tp>
inline typename std::enable_if<I == sizeof...(Tp), bool>::type set(State &state, std::tuple<Tp...> &t)
{
    return true;
}

template <std::size_t I = 0, class... Tp>
    inline typename std::enable_if < I<sizeof...(Tp), bool>::type set(State &state, std::tuple<Tp...> &t)
{
    using type = typename std::tuple_element<I, std::tuple<Tp...>>::type;
    bool success = argument<type>(state, I + 1, std::get<I>(t));
    if (success)
    {
        return set<I + 1, Tp...>(state, t);
    }
    return false;
}

template <class F, class... T>
inline int arguments(State &state, F func)
{
    std::tuple<T...> args;
    if (set(state, args))
    {
        return result(state, std::apply(func, args));
    }
    return 0;
}

template <class F>
struct FnArgs;

template <class R, class... T>
struct FnArgs<R (*)(T...)>
{
    template <class F>
    static int invoke(State &state, F func)
    {
        return arguments<F, T...>(state, func);
    }
};

template <class F>
class Bind
{
    F m_args;

public:
    Bind(F f) : m_args(f)
    {
    }

    int operator()(State &state)
    {
        return FnArgs<F>::invoke(state, m_args);
    }
};

} // namespace lua

#endif