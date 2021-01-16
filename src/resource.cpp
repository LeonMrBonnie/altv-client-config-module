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
    // todo: delete custom funcs
    // todo: delete custom vars
    
    return true;
}

bool ConfigResource::OnEvent(const alt::CEvent* ev)
{
    // Get all functions that should be executed for the current event
    auto funcs = eventFuncs.equal_range(ev->GetType());
    for(auto it = funcs.first; it != funcs.second; ++it)
    {
       for(auto func : it->second)
       {
           // Call the function with its arguments
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
        Util::Natives::Invoke(ctx.Get(), native.first, native.second);
    }
    #endif
}

void ConfigResource::LoadFile(std::string name)
{
    // Check if file is already loaded
    if(std::find(loadedFiles.begin(), loadedFiles.end(), name) != loadedFiles.end()) return;
    // Add file to loaded files to avoid recursion
    loadedFiles.emplace_back(name);

    // Parse the file
    Parser::File file(this, name);
    file.Parse();
}
