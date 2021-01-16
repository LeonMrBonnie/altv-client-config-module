#pragma once

#include "alt-config/alt-config.h"
#include "Log.h"

namespace Parser
{
    class Event
    {
        alt::CEvent::Type type;
        std::string name;

        static std::vector<Event*> all;

    public:

        Event(alt::CEvent::Type type, std::string name);

        alt::CEvent::Type GetType()
        {
            return type;
        }
        std::string GetName()
        {
            return name;
        }

        static Event* Get(std::string name);
        static Event* Get(alt::CEvent::Type type);
    };
};
