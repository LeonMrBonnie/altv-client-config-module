#pragma once

#include "alt-config/alt-config.h"
#include "Log.h"
#include "util/config.h"

class ConfigResource;
namespace Parser
{
    using ArgsArray = alt::Array<alt::config::Node>;

    class Function
    {
        using FuncHandler = void(*)(alt::Array<alt::config::Node> args);

        static std::vector<Function*> all;
        static Function* Get(std::string name);

        std::string name;
        FuncHandler handler;

    public:
        Function(std::string name, FuncHandler handler)
        : name(name),
          handler(handler)
        {
            all.emplace_back(this);
        }
        void Call(ArgsArray args);

        static std::pair<Function*, ArgsArray> Parse(alt::config::Node node, ConfigResource* resource);
    };
};
