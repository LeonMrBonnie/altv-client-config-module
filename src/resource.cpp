#include "resource.h"

bool ConfigResource::Start()
{
    // Read main file
    auto pkg = resource->GetPackage();
    alt::IPackage::File* main = pkg->OpenFile(resource->GetMain());
    alt::String src(pkg->GetFileSize(main));
    pkg->ReadFile(main, src.GetData(), src.GetSize());
    pkg->CloseFile(main);

    // Parse config
    alt::config::Parser parser(src.CStr(), src.GetSize());
    try
    {
        auto config = parser.Parse();
        Parse(config);
    }
    catch(const alt::config::Error& e)
    {
        Log::Error << "Error while parsing main file:" << Log::Endl;
        Log::Error << e.what() << Log::Endl;
        return false;
    }

    return true;
}

void ConfigResource::Parse(alt::config::Node config)
{
    //Log::Info << config["test"].ToString().c_str() << Log::Endl;
    // TODO: Parse config
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
