#include "resource.h"

bool ConfigResource::Start()
{
    try
    {
        // Read and parse main file
        auto main = resource->GetMain().ToString();
        auto config = ReadConfig(main);
        ParseConfig(main, config);
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

void ConfigResource::ParseConfig(std::string file, alt::config::Node config)
{
    // Add file to loaded files to avoid infinite include recursion
    loadedFiles.emplace_back(file);

    try {
        // Load includes
        auto includes = config["includes"];
        ParseIncludes(includes);

        // Load every tick natives
        auto natives = config["everyTick"];
        ParseNatives(natives);
    }    
    catch(...) {}
}

void ConfigResource::ParseIncludes(alt::config::Node includes)
{
    if(!includes.IsList()) return;
    for(auto include : includes.ToList())
    {
        auto name = include.ToString();
        // Check if include is already loaded
        if(std::find(loadedFiles.begin(), loadedFiles.end(), name) != loadedFiles.end()) continue;
        // Read and parse the include
        auto includeConfig = ReadConfig(name);
        ParseConfig(name, includeConfig);
    }
}

void ConfigResource::ParseNatives(alt::config::Node natives)
{
    if(!natives.IsList()) return;
    // todo: Parse natives
}
