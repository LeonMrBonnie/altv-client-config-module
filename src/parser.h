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

        void ParseIncludes();
        void ParseNatives();

    public:
        File(ConfigResource* resource, std::string name);
        ~File() = default;

        void Parse();
    };
};
