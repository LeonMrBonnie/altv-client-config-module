#pragma once

#include "Log.h"
#include "alt-config/alt-config.h"
#include "funcs.h"

class ConfigResource;
namespace Parser
{
    static const std::map<std::string, alt::CEvent::Type> events = {
        { "resourceStart", alt::CEvent::Type::RESOURCE_START },
        { "resourceStop", alt::CEvent::Type::RESOURCE_STOP },
        #ifdef SERVER_MODULE
        { "playerConnect", alt::CEvent::Type::PLAYER_CONNECT },
        { "playerDisconnect", alt::CEvent::Type::PLAYER_DISCONNECT},
        #endif
        { "consoleCommand", alt::CEvent::Type::CONSOLE_COMMAND_EVENT }
    };
    static alt::CEvent::Type GetEventType(std::string eventName);

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
