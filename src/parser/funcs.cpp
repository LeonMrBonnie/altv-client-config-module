#include "parser.h"

using namespace Parser;

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

bool File::IsFunction(std::string name)
{
    bool found = false;
    if(Parser::funcs.find(name) != Parser::funcs.end()) found = true;
    // todo: add custom funcs to resource
    //else if(resource->customFuncs.find(name) != resource->customFuncs.end()) found = true;
    return found;
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
