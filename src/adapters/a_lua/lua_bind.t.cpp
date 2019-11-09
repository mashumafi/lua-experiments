#include "lua_bind.h"
#include "lua_state.h"

#include <catch2/catch.hpp>

double test0(double, double)
{
    return 1.1;
}

TEST_CASE("Bind zero argument")
{
    lua::ManagedState state;

    lua::Bind fn1(test0);

    lua::Bind fn2([](double, double) -> double {
        return 2.2;
    });

    /*using namespace std::placeholders;
    lua::Bind fn3(std::bind(test0, _1, _2));

    state.bind("test0_raw", fn1);
    state.bind("test0_lambda", fn2);

    int rc = state.dostring("test0_raw()");
    REQUIRE(0 == rc);
    rc = state.dostring("test0_lambda()");
    REQUIRE(0 == rc);
    state.bind("test0_bind", fn3);*/
}
/*
TEST_CASE("Bind one argument")
{
    lua::ManagedState state;
    auto fn = lua::Bind([](double) {
        return 0.0;
    });
    state.bind("test1", fn);
}

TEST_CASE("Bind one argument")
{
    lua::ManagedState state;
    auto fn = lua::Bind([](double, double) {
        return 0.0;
    });
    state.bind("test2", fn);
}

TEST_CASE("Bind three argument")
{
    lua::ManagedState state;
    auto fn = lua::Bind([](double, double, double) {
        return 0.0;
    });
    state.bind("test3", fn);
}
*/