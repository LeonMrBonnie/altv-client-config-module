#pragma once

#include "Log.h"
#include "alt-config/alt-config.h"

class ConfigResource;
namespace Parser
{
    class File
    {
        ConfigResource* resource;
        std::string name;
        alt::config::Node config;

        void ParseIncludes(alt::config::Node includes);
        void ParseNatives(alt::config::Node natives);

    public:
        File(ConfigResource* resource, std::string name);
        ~File() = default;

        void Parse();
    };
};
