#include "parser.h"
#include "resource.h"

using namespace Parser;

alt::CEvent::Type Parser::GetEventType(std::string eventName)
{
    try {
        return events.at(eventName);
    }
    catch(...)
    {
        return alt::CEvent::Type::NONE;
    }
}

File::File(ConfigResource* resource, std::string name)
: resource(resource),
  name(name)
{
    auto pkg = resource->GetResource()->GetPackage();
    alt::IPackage::File* pkgFile = pkg->OpenFile(name);
    alt::String src(pkg->GetFileSize(pkgFile));
    pkg->ReadFile(pkgFile, src.GetData(), src.GetSize());
    pkg->CloseFile(pkgFile);

    alt::config::Parser parser(src.CStr(), src.GetSize());
    config = parser.Parse();
}

// Parse

void File::Parse()
{
    try {
        // Load includes
        ParseIncludes();

        #ifdef CLIENT_MODULE
        // Load every tick natives
        ParseNatives();
        #endif

        // Parse Main
        ParseMain();

        // Parse event handlers
        ParseEventHandlers();

        // todo: custom functions, variables, event handlers, natives
    }    
    catch(...) {}
}

void File::ParseIncludes()
{
    auto includes = config["includes"];
    if(!includes.IsList()) return;
    for(auto include : includes.ToList())
    {
        auto name = include.ToString();
        // Read and parse the include
        resource->LoadFile(name);
    }
}

#ifdef CLIENT_MODULE
void File::ParseNatives()
{
    auto natives = config["everyTick"];
    if(!natives.IsList()) return;
    // todo: Parse natives
}
#endif

void File::ParseMain()
{
    auto main = config["main"];
    if(!main.IsList()) return;
    // Get all functions out of the list
    for(auto node : main.ToList())
    {
        // Parse the function
        auto func = Parser::Function::Parse(node, resource);
        if(func.first == nullptr) continue;
        // Call the function
        func.first->Call(func.second);
    }
}

void File::ParseEventHandlers()
{
    auto handlers = config["eventHandlers"];
    if(!handlers.IsDict()) return;
    auto dict = handlers.ToDict();
    for(auto node : dict)
    {
        if(!node.second.IsList()) continue;
        auto event = Parser::GetEventType(node.first);
        if(event == alt::CEvent::Type::NONE) continue;
        for(auto func : node.second.ToList())
        {
            auto pair = Function::Parse(func, resource);
            if(pair.first == nullptr) continue;
            resource->RegisterEventFunc(event, pair.first, pair.second);
        }
    }
}
