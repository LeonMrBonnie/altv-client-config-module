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

// Call function

void File::CallFunction(std::string name, alt::Array<alt::config::Node> args)
{
    auto func = Parser::funcs.find(name);
    if(func == Parser::funcs.end())
    {
        Log::Error << "Tried to call invalid function: " << name.c_str() << Log::Endl;
        return;
    }
    func->second(args);
}

// Funcs
Parser::Func logFunc("log", [](alt::Array<alt::config::Node> args) {
    for(auto arg : args)
    {
        Log::Colored << arg.ToString() << " ";
    }
    Log::Colored << Log::Endl;
});

Parser::Func logWarnFunc("logWarning", [](alt::Array<alt::config::Node> args) {
    for(auto arg : args)
    {
        Log::Warning << arg.ToString() << " ";
    }
    Log::Warning << Log::Endl;
});

Parser::Func logErrorFunc("logError", [](alt::Array<alt::config::Node> args) {
    for(auto arg : args)
    {
        Log::Error << arg.ToString() << " ";
    }
    Log::Error << Log::Endl;
});
