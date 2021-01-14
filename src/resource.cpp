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
    return true;
}

bool ConfigResource::OnEvent(const alt::CEvent* ev)
{
    //Log::Info << "Event received: " << std::to_string((uint16_t)ev->GetType()) << Log::Endl;
    return true;
}

void ConfigResource::OnTick()
{
    static auto ctx = alt::ICore::Instance().CreateNativesContext();

    // Invoke all every tick natives
    for(auto native : tickNatives)
    {
        Natives::Invoke(ctx.Get(), native.first, native.second);
    }
}

void ConfigResource::LoadFile(std::string name)
{
    if(std::find(loadedFiles.begin(), loadedFiles.end(), name) != loadedFiles.end()) return;
    loadedFiles.emplace_back(name);

    Parser::File file(this, name);
    file.Parse();
}
