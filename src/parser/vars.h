#pragma once

#include "alt-config/alt-config.h"
#include "Log.h"

class ConfigResource;
namespace Parser
{
    class Variable
    {
        using GetterFunc = alt::config::Node (*)(ConfigResource* resource);
        static std::vector<Variable*> all;

        std::string name;
        GetterFunc getter;

        alt::config::Node Value(ConfigResource* resource)
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

        static alt::config::Node Parse(alt::config::Node node, ConfigResource* resource);
        static Variable* Get(std::string name);
    };
};
