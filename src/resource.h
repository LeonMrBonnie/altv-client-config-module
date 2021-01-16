#pragma once

#include "cpp-sdk/SDK.h"
#include "alt-config/alt-config.h"
#include "Log.h"
#include "util/natives.h"
#include "parser/parser.h"

class ConfigRuntime;
class ConfigResource : public alt::IResource::Impl
{   
    using Func = std::map<Parser::Function*, alt::Array<alt::config::Node>>;

    ConfigRuntime* runtime;
    alt::IResource* resource;

    std::vector<std::string> loadedFiles;
    std::unordered_multimap<alt::CEvent::Type, Func> eventFuncs;
    #ifdef CLIENT_MODULE
    std::unordered_multimap<alt::INative*, alt::Array<void*>> tickNatives;
    #endif
    //std::unordered_map<std::string, void*> variables;
    //std::vector<Function*> funcs;

public:
    ConfigResource(ConfigRuntime* runtime, alt::IResource* resource) : runtime(runtime), resource(resource) {};
    ~ConfigResource() = default;
    alt::IResource* GetResource()
    {
        return resource;
    }
    void LoadFile(std::string file);
    void RegisterEventFunc(alt::CEvent::Type event, Parser::Function* func, alt::Array<alt::config::Node> args)
    {
        eventFuncs.insert({ event, Func({ {func, args} }) });
    }

    bool Start();
    bool Stop();

    bool OnEvent(const alt::CEvent* event);
    void OnTick();

    void OnCreateBaseObject(alt::IBaseObject* object) {}
    void OnRemoveBaseObject(alt::IBaseObject* object) {}
};

