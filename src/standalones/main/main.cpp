#include "main.h"

Main::Instance::Instance(ArgType &&arguments) : m_arguments(std::move(arguments))
{
}

const ArgType &Main::Instance::arguments() const
{
    return m_arguments;
}

int main(int argc, const char *argv[])
{
    ArgType args(argc);
    for (int i = 0; i < args.size(); i++)
    {
        args[i] = argv[i];
    }
    Main::Instance instance(std::move(args));
    return instance.main();
}
