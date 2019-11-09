#ifndef LOGGER_H
#define LOGGER_H

#include "singleton.h"

#include <iostream>
#include <memory>
#include <string_view>

namespace logger
{

class Logger
{
public:
    class Instance
    {
    public:
        void print(std::string_view text)
        {
            std::cout << text << std::endl;
        }
    };

    static Instance *instance()
    {
        return Scoped::instance();
    }

    using Scoped = Singleton<Instance>;
};

} // namespace logger

#endif
