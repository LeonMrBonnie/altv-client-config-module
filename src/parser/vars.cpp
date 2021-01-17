#include "vars.h"
#include "../util/config.h"
#include <regex>
#include "../resource.h"

using namespace Parser;

std::vector<Variable*> Variable::all = std::vector<Variable*>();

// Regex to get variable from node
// 'var(test123)' becomes 'test123'
static std::regex regex("var\\((.*)\\)");

alt::config::Node Variable::Parse(alt::config::Node node, ConfigResource* resource)
{
    if(!Util::Config::VerifyNodeType(node, "string", true)) return alt::config::Node();

    // Check if node has variable and if yes, check if it exists
    std::smatch results;
    auto str = node.ToString();
    auto result = std::regex_search(str.cbegin(), str.cend(), results, regex);
    if(!result) return alt::config::Node();

    // Check if a variable with that name exists
    auto var = results[1].str();
    auto found = Get(var);
    // todo: get custom variables from resource
    if(found == nullptr)
    {
        Log::Error << "Invalid variable specified: " << var << Log::Endl;
        return alt::config::Node();
    }
    return found->Value(resource);
}

Variable* Variable::Get(std::string name)
{
    for(auto var : all)
    {
        if(var->name == name) return var;
    }
    return nullptr;
}

// Variables

Variable resourceName("resourceName", [](ConfigResource* resource) {
    auto name = resource->GetResource()->GetName();
    return alt::config::Node(name.CStr());
});
