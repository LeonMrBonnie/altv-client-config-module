#pragma once

#include "alt-config/alt-config.h"
#include "Log.h"

namespace Util
{
    namespace Config
    {
        // Gets type as string from config node
        static std::string GetNodeType(alt::config::Node node)
        {
            if(node.IsScalar()) return "string";
            if(node.IsDict()) return "dict";
            if(node.IsList()) return "list";
            if(node.IsNone()) return "none";
            return "none";
        }

        // Verifies if node type is the specified node type
        static bool VerifyNodeType(alt::config::Node node, std::string expectedType, bool noErrorOnNone = false)
        {
            auto type = GetNodeType(node);
            if(expectedType != type)
            {
                if(type != "none" || !noErrorOnNone) Log::Error << "Expected type '" << expectedType << "' but received type '" << type << "'" << Log::Endl;
                return false;
            }
            return true;
        }
    }
}
