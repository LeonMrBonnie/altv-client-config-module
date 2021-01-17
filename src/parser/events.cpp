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
Event resourceStart(alt::CEvent::Type::RESOURCE_START, "resourceStart", [](const alt::CEvent* event, alt::Array<void*> args) {
    auto ev = static_cast<const alt::CResourceStartEvent*>(event);
    args.Push(&ev->GetResource()->GetName().ToString());
    return args;
});
Event resourceStop(alt::CEvent::Type::RESOURCE_STOP, "resourceStop", [](const alt::CEvent* event, alt::Array<void*> args) {
    auto ev = static_cast<const alt::CResourceStopEvent*>(event);
    args.Push(&ev->GetResource()->GetName().ToString());
    return args;
});
Event resourceError(alt::CEvent::Type::RESOURCE_ERROR, "resourceError", [](const alt::CEvent* event, alt::Array<void*> args) {
    auto ev = static_cast<const alt::CResourceErrorEvent*>(event);
    args.Push(&ev->GetResource()->GetName().ToString());
    return args;
});
#ifdef SERVER_MODULE
Event playerConnect(alt::CEvent::Type::PLAYER_CONNECT, "playerConnect", [](const alt::CEvent* event, alt::Array<void*> args) {
    auto ev = static_cast<const alt::CResourceStartEvent*>(event);
    args.Push(&ev->GetResource()->GetName().ToString());
    return args;
});
Event playerDisconnect(alt::CEvent::Type::PLAYER_DISCONNECT, "playerDisconnect", [](const alt::CEvent* event, alt::Array<void*> args) {
    auto ev = static_cast<const alt::CPlayerDisconnectEvent*>(event);
    args.Push(&ev->GetTarget());
    args.Push(&ev->GetReason().ToString());
    return args;
});
#endif
Event consoleCommand(alt::CEvent::Type::CONSOLE_COMMAND_EVENT, "consoleCommand", [](const alt::CEvent* event, alt::Array<void*> args) {
    auto ev = static_cast<const alt::CConsoleCommandEvent*>(event);
    args.Push(&ev->GetName().ToString());
    for(auto arg : ev->GetArgs())
    {
        args.Push(&arg.ToString());
    }
    return args;
});
