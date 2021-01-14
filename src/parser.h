#pragma once

#include "Log.h"
#include "alt-config/alt-config.h"

class ConfigResource;
namespace Parser
{
    using FuncHandler = void(*)(alt::Array<alt::config::Node> args);
    static std::map<std::string, FuncHandler> funcs;

    class Func
    {
    public:
        Func(std::string name, FuncHandler handler)
        {
            funcs.insert({name, handler});
        }
    };

    class File
    {
        ConfigResource* resource;
        std::string name;
        alt::config::Node config;
        void CallFunction(std::string name, alt::Array<alt::config::Node> args);

        void ParseIncludes();
        void ParseNatives();
        void ParseMain();

    public:
        File(ConfigResource* resource, std::string name);
        ~File() = default;

        void Parse();
    };
};
