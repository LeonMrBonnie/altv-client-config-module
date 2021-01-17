#pragma once

#include "alt-config/alt-config.h"
#include "Log.h"

class ConfigResource;
namespace Parser
{
    class Variable
    {
        using GetterFunc = void* (*)(ConfigResource* resource);
        static std::vector<Variable*> all;

        std::string name;
        GetterFunc getter;

        void* Value(ConfigResource* resource)
        {
            return getter(resource);
        }

    public:
        Variable(std::string name, GetterFunc getter)
        : name(name),
          getter(getter)
        {
            all.emplace_back(this);
        }

        static void* Parse(alt::config::Node node, ConfigResource* resource);
        static Variable* Get(std::string name);
    };
};
