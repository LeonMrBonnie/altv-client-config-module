#pragma once

#include "alt-config/alt-config.h"
#include "Log.h"

namespace Parser
{
    class Event
    {
        using ArgsGetter = alt::Array<void*>(*)(const alt::CEvent* event, alt::Array<void*> args);
        alt::CEvent::Type type;
        std::string name;
        ArgsGetter argsGetter;

        static std::vector<Event*> all;

    public:

        Event(alt::CEvent::Type type, std::string name, ArgsGetter argsGetter)
        : type(type),
          name(name),
          argsGetter(argsGetter)
        {};

        alt::CEvent::Type GetType()
        {
            return type;
        }
        std::string GetName()
        {
            return name;
        }
        alt::Array<void*> GetArgs(const alt::CEvent* event)
        {
            return argsGetter(event, alt::Array<void*>());
        }

        static Event* Get(std::string name);
        static Event* Get(alt::CEvent::Type type);
    };
};
