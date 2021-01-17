#include "events.h"

using namespace Parser;

std::vector<Event*> Event::all = std::vector<Event*>();

Event* Event::Get(std::string name)
{
    for(auto event : all)
    {
        if(event->name == name) return event;
    }
    return nullptr;
}

Event* Event::Get(alt::CEvent::Type type)
{
    for(auto event : all)
    {
        if(event->type == type) return event;
    }
    return nullptr;
}

// Events
Event resourceStart(alt::CEvent::Type::RESOURCE_START, "resourceStart");
Event resourceStop(alt::CEvent::Type::RESOURCE_STOP, "resourceStop");
Event resourceError(alt::CEvent::Type::RESOURCE_ERROR, "resourceError");
#ifdef SERVER_MODULE
Event playerConnect(alt::CEvent::Type::PLAYER_CONNECT, "playerConnect");
Event playerDisconnect(alt::CEvent::Type::PLAYER_DISCONNECT, "playerDisconnect");
#endif
Event consoleCommand(alt::CEvent::Type::CONSOLE_COMMAND_EVENT, "consoleCommand");
