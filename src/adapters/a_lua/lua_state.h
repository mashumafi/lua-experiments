#ifndef LUA_STATE_INCLUDED
#define LUA_STATE_INCLUDED

#include <functional>
#include <unordered_map>
#include <string_view>

struct lua_State;

namespace lua
{

class State
{
    using Function = std::function<int(State &)>;
    using Functions = std::unordered_map<std::string_view, Function>;
    using Bindings = std::unordered_map<lua_State *, Functions>;

public:
    virtual ~State() {}

    void openlibs();

    int gettop();
    void setglobal(std::string_view name);

    int loadfile(std::string_view name);
    int dofile(std::string_view name);
    int dostring(std::string_view s);

    void bind(std::string_view name, Function fn);

    int isnumber(int idx);
    int isstring(int idx);
    int isuserdata(int idx);

    std::string_view tostring(int idx);
    double tonumber(int idx);
    void *touserdata(int idx);

    template <class T, class... Args>
    T *newuserdata(Args... args)
    {
        return new (newuserdata(sizeof(T))) T(args...);
    }
    void *newuserdata(size_t sz);

    void push(std::string_view value);
    void push(double value);

    int error();
    int error(std::string_view fmt);

    void stacktrace();
    std::string_view currentFunction();

protected:
    State(lua_State *L);
    lua_State *m_state;
    static Bindings d_bindings;

private:
    static int handleFunction(lua_State *L);
};

class ManagedState : public State
{
public:
    ManagedState();
    virtual ~ManagedState();
};

} // namespace lua

#endif
