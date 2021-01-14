#pragma once

#include "cpp-sdk/SDK.h"
#include "alt-config/alt-config.h"
#include "Log.h"
#include "natives.h"

class ConfigRuntime;
class ConfigResource : public alt::IResource::Impl
{   
    ConfigRuntime* runtime;
    alt::IResource* resource;

    std::vector<std::string> loadedFiles;
    //using EventHandler = std::function<void>;
    //std::unordered_multimap<alt::CEvent::Type, EventHandler> eventHandlers;
    std::unordered_multimap<alt::INative*, alt::Array<void*>> tickNatives;

public:
    ConfigResource(ConfigRuntime* runtime, alt::IResource* resource) : runtime(runtime), resource(resource) {};
    ~ConfigResource() = default;

    bool Start();
    bool Stop();

    bool OnEvent(const alt::CEvent* event);
    void OnTick();

    void OnCreateBaseObject(alt::IBaseObject* object) {}
    void OnRemoveBaseObject(alt::IBaseObject* object) {}

    void Parse(std::string file, alt::config::Node config);
    alt::config::Node ReadConfig(std::string file);
};
