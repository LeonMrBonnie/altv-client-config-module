#include "parser.h"
#include "funcs.h"

using namespace Parser;

std::vector<Function*> Function::all = std::vector<Function*>();

std::pair<Function*, ArgsArray> Function::Parse(alt::config::Node node, ConfigResource* resource)
{
    if(!node.IsDict()) return std::pair(nullptr, ArgsArray());
    auto func = node["function"];
    if(!Util::Config::VerifyNodeType(func, "string")) return std::pair(nullptr, ArgsArray());
    auto args = node["args"];
    alt::Array<alt::config::Node> argsArray;
    if(args.IsList())
    {
        for(auto arg : args.ToList())
        {
            // todo: parse variables
            argsArray.Push(arg);
        }
    }

    auto found = Get(func.ToString());
    // todo: add custom funcs to resource
    if(found == nullptr) 
    {
        Log::Error << "Invalid function specified: " << func.ToString() << Log::Endl;
        return std::pair(nullptr, ArgsArray());
    }
    return std::pair(found, argsArray);
}

Function* Function::Get(std::string name)
{
    for(auto func : all)
    {
        if(func->name == name) return func;
    }
    return nullptr;
}

void Function::Call(ArgsArray args)
{
    this->handler(args);
}

// Funcs
Function logFunc("log", [](alt::Array<alt::config::Node> args) {
    for(auto arg : args)
    {
        Log::Colored << arg.ToString() << " ";
    }
    Log::Colored << Log::Endl;
});

Function logWarnFunc("logWarning", [](alt::Array<alt::config::Node> args) {
    for(auto arg : args)
    {
        Log::Warning << arg.ToString() << " ";
    }
    Log::Warning << Log::Endl;
});

Function logErrorFunc("logError", [](alt::Array<alt::config::Node> args) {
    for(auto arg : args)
    {
        Log::Error << arg.ToString() << " ";
    }
    Log::Error << Log::Endl;
});
