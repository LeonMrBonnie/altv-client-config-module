#include "resource.h"
#include "parser/parser.h"

bool ConfigResource::Start()
{
    try
    {
        // Read and parse main file
        auto main = resource->GetMain().ToString();
        LoadFile(main);
    }
    catch(const alt::config::Error& e)
    {
        Log::Error << "Error while parsing: ";
        Log::Error << e.what() << Log::Endl;
        return false;
    }

    return true;
}

bool ConfigResource::Stop()
{
    // Clean up
    loadedFiles.clear();
    eventFuncs.clear();
    #ifdef CLIENT_MODULE
    tickNatives.clear();
    #endif
    
    return true;
}

bool ConfigResource::OnEvent(const alt::CEvent* ev)
{
    //Log::Info << "Event received: " << std::to_string((uint16_t)ev->GetType()) << Log::Endl;
    auto funcs = eventFuncs.equal_range(ev->GetType());
    for(auto it = funcs.first; it != funcs.second; ++it)
    {
       for(auto func : it->second)
       {
           func.first->Call(func.second);
       }
    }
    return true;
}

void ConfigResource::OnTick()
{
    #ifdef CLIENT_MODULE
    static auto ctx = alt::ICore::Instance().CreateNativesContext();

    // Invoke all every tick natives
    for(auto native : tickNatives)
    {
        Natives::Invoke(ctx.Get(), native.first, native.second);
    }
    #endif
}

void ConfigResource::LoadFile(std::string name)
{
    if(std::find(loadedFiles.begin(), loadedFiles.end(), name) != loadedFiles.end()) return;
    loadedFiles.emplace_back(name);

    Parser::File file(this, name);
    file.Parse();
}
