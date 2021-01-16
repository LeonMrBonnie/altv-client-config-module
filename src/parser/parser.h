#pragma once

#include "Log.h"
#include "alt-config/alt-config.h"
#include "funcs.h"
#include "events.h"

class ConfigResource;
namespace Parser
{
    class File
    {
        ConfigResource* resource;
        std::string name;
        alt::config::Node config;

        void ParseMain();
        void ParseIncludes();
        #ifdef CLIENT_MODULE
        void ParseNatives();
        #endif
        void ParseEventHandlers();

    public:
        File(ConfigResource* resource, std::string name);
        ~File() = default;

        void Parse();
    };
};
