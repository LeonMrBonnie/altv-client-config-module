#pragma once

#include "alt-config/alt-config.h"
#include "Log.h"

namespace Util
{
    namespace Config
    {
        std::string GetNodeType(alt::config::Node node)
        {
            if(node.IsScalar()) return "string";
            if(node.IsDict()) return "dict";
            if(node.IsList()) return "list";
            if(node.IsNone()) return "none";
        }

        bool VerifyNodeType(alt::config::Node node, std::string expectedType, bool showError = true)
        {
            auto type = GetNodeType(node);
            if(expectedType != type)
            {
                if(showError) Log::Error << "Expected type '" << expectedType << "' but received type '" << type << "'" << Log::Endl;
                return false;
            }
            return true;
        }
    }
}
