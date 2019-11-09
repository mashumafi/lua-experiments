#include <allocator.h>
#include <default_allocator.h>
#include <system_allocator.h>
#include <logger.h>
#include <lua_bind.h>
#include <lua_state.h>
#include <main.h>
#include <sqlite_database.h>

#include <array>
#include <iostream>
#include <functional>
#include <fstream>
#include <streambuf>
#include <string>
#include <tuple>

static int average(lua::State &state)
{
    int n = state.gettop();
    double sum = 0;
    int i;

    for (i = 1; i <= n; i++)
    {
        if (!state.isnumber(i))
        {
            state.push("Incorrect argument to 'average'");
            state.error();
        }
        sum += state.tonumber(i);
    }

    state.push(sum / n);
    state.push(sum);

    return 2;
}

static std::tuple<double, double> ez_average(lua::Variadic<double> args)
{
    double sum = 0;
    for (const double &&i : args)
    {
        sum += i;
    }
    return std::make_tuple(sum / args.size(), sum);
}

#define VERSION "0.7"

void lua_test()
{
    lua::ManagedState state;
    state.openlibs();

    state.push(VERSION);
    state.setglobal("VERSION");

    state.bind("average", average);
    state.bind("ez_average", lua::Bind(ez_average));
    int rc = state.dofile("./scripts/average.lua");

    if (rc != 0)
    {
        if (state.isstring(state.gettop()))
            std::cout << "Error(" << rc << "): " << state.tostring(state.gettop()) << std::endl;
    }
}

void sqlite_test()
{
    sqlite::Database db;

    std::ifstream t("./sql/friends.sql");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    std::string_view sql = str;
    while (!sql.empty())
    {
        if (sqlite::Statement createTable = db.prepare(sql, sql))
        {
            if (!createTable.step())
            {
                std::cout << __LINE__ << " " << db.errmsg() << std::endl;
            }
        }
    }

    if (sqlite::Statement createTable = db.prepare("SELECT Id, Name FROM Friends"))
    {
        for (auto row : createTable.step<int, std::string_view>())
        {
            std::cout << "Id: " << std::get<0>(row) << ", Name: " << std::get<1>(row) << std::endl;
        }
    }
    else
    {
        std::cout << db.errmsg() << std::endl;
    }
}

void logger_test()
{
    logger::Logger::Scoped scopedLog;
    logger::Logger::Instance *log = logger::Logger::instance();
    log->print("Hello world!");
}

void allocator_test()
{
    allocator::SystemAllocator allocator;
    allocator::DefaultAllocator::Scoped scopedAllocator(&allocator);

    allocator::DefaultAllocator::Instance *defaultAllocator = allocator::DefaultAllocator::instance();
    void *mem = defaultAllocator->malloc(1000);
    defaultAllocator->free(mem);
}

int Main::Instance::main()
{
    lua_test();
    sqlite_test();
    logger_test();
    allocator_test();

    return 0;
}