#include "lua_state.h"

#include <iostream>

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace lua
{

State::Bindings State::d_bindings;

State::State(lua_State *L) : m_state(L)
{
}

void State::openlibs()
{
	luaL_openlibs(m_state);
}

int State::gettop()
{
	return lua_gettop(m_state);
}

void State::setglobal(std::string_view name)
{
	lua_setglobal(m_state, name.data());
}

int State::loadfile(std::string_view name)
{
	return luaL_loadfile(m_state, name.data());
}

int State::dofile(std::string_view name)
{
	return luaL_dofile(m_state, name.data());
}

void State::bind(std::string_view name, Function fn)
{
	Bindings::iterator binding = d_bindings.find(m_state);
	if (binding == d_bindings.end())
	{
		binding = d_bindings.insert(d_bindings.end(), std::pair(m_state, Functions()));
	}
	Functions &functions = binding->second;
	functions.emplace(name, fn);

	lua_register(m_state, name.data(), handleFunction);
}

int State::handleFunction(lua_State *L)
{
	State state(L);
	try
	{
		return State::d_bindings[L][state.currentFunction()](state);
	}
	catch (const std::exception &e)
	{
		state.push(e.what());
		state.error();
		return 0;
	}
}

int State::isnumber(int idx)
{
	return lua_isnumber(m_state, idx);
}

int State::isstring(int idx)
{
	return lua_isstring(m_state, idx);
}

int State::isuserdata(int idx)
{
	return lua_isuserdata(m_state, idx);
}

double State::tonumber(int idx)
{
	return lua_tonumber(m_state, idx);
}

std::string_view State::tostring(int idx)
{
	return lua_tostring(m_state, idx);
}

void *State::touserdata(int idx)
{
	return lua_touserdata(m_state, idx);
}

void *State::newuserdata(size_t sz)
{
	return lua_newuserdata(m_state, sz);
}

void State::push(std::string_view value)
{
	lua_pushstring(m_state, value.data());
}

void State::push(double value)
{
	lua_pushnumber(m_state, value);
}

int State::error()
{
	return lua_error(m_state);
}

int State::error(std::string_view fmt)
{
	return luaL_error(m_state, fmt.data());
}

void State::stacktrace()
{
	lua_Debug info;
	int level = 0;
	while (lua_getstack(m_state, level, &info))
	{
		lua_getinfo(m_state, "nSl", &info);
		fprintf(stderr, "  [%d] %s:%d -- %s [%s]\n",
				level, info.short_src, info.currentline,
				(info.name ? info.name : "<unknown>"), info.what);
		++level;
	}
}

std::string_view State::currentFunction()
{
	lua_Debug info;
	if (lua_getstack(m_state, 0, &info))
	{
		lua_getinfo(m_state, "n", &info);
		return info.name ? info.name : "";
	}
	return "";
}

ManagedState::ManagedState() : State(luaL_newstate())
{
}

ManagedState::~ManagedState()
{
	lua_close(m_state);
	d_bindings.erase(m_state);
}

} // namespace lua