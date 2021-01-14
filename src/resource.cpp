#include "resource.h"

bool ConfigResource::Start()
{
    try
    {
        auto main = resource->GetMain().ToString();
        auto config = ReadConfig(main);
        Parse(main, config);
    }
    catch(const alt::config::Error& e)
    {
        Log::Error << "Error while parsing:" << Log::Endl;
        Log::Error << e.what() << Log::Endl;
        return false;
    }

    return true;
}

alt::config::Node ConfigResource::ReadConfig(std::string file)
{
    auto pkg = resource->GetPackage();
    alt::IPackage::File* pkgFile = pkg->OpenFile(file);
    alt::String src(pkg->GetFileSize(pkgFile));
    pkg->ReadFile(pkgFile, src.GetData(), src.GetSize());
    pkg->CloseFile(pkgFile);

    alt::config::Parser parser(src.CStr(), src.GetSize());
    return parser.Parse();
}

void ConfigResource::Parse(std::string file, alt::config::Node config)
{
    loadedFiles.emplace_back(file);
    try {
        auto includes = config["includes"].ToList();
        for(auto include : includes)
        {
            auto name = include.ToString();
            if(std::find(loadedFiles.begin(), loadedFiles.end(), name) != loadedFiles.end()) continue;
            auto includeConfig = ReadConfig(name);
            Parse(name, includeConfig);
        }
    }
    catch(...) {}
    Log::Info << config["test"].ToString().c_str() << Log::Endl;
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

void ConfigResource::OnTick()
{
    static auto ctx = alt::ICore::Instance().CreateNativesContext();

    for(auto native : tickNatives)
    {
        Natives::Invoke(ctx.Get(), native.first, native.second);
    }
}
