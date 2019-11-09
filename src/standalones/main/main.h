#ifndef MAIN_MAIN_H
#define MAIN_MAIN_H

#include <singleton.h>

#include <string_view>
#include <vector>

using ArgType = std::vector<std::string_view>;

class Main
{
public:
    class Instance
    {
    public:
        Instance(ArgType &&arguments);
        int main();
        const ArgType &arguments() const;

    private:
        ArgType m_arguments;
    };

    static Instance *instance()
    {
        return Scoped::instance();
    }

    using Scoped = Singleton<Instance, ArgType>;
};

#endif
