#include "parser.h"
#include "resource.h"

using namespace Parser;

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

        // Load every tick natives
        ParseNatives();

        // Parse Main
        ParseMain();

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

void File::ParseNatives()
{
    auto natives = config["everyTick"];
    if(!natives.IsList()) return;
    // todo: Parse natives
}

void File::ParseMain()
{
    auto main = config["main"];
    if(!main.IsList()) return;
    for(auto node : main.ToList())
    {
        if(!node.IsDict()) continue;
        auto func = node["function"];
        if(!func.IsScalar()) {
            Log::Error << "Invalid dict passed to main list" << Log::Endl;
            return;
        }
        auto args = node["args"];
        alt::Array<alt::config::Node> argsArray;
        if(args.IsList())
        {
            for(auto arg : args.ToList())
            {
               argsArray.Push(arg);
            }
        }
        CallFunction(func.ToString(), argsArray);
    }
}
