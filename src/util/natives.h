#pragma once

#include "cpp-sdk/SDK.h"
#include "Log.h"

#ifdef CLIENT_MODULE
class Natives
{
public:
    static void Invoke(alt::INative::Context* ctx, alt::INative* native, alt::Array<void*> args)
    {
        if(!native->IsValid()) return;
        auto argTypes = native->GetArgTypes();

        for(int i = 0, size = argTypes.GetSize(); i < size; i++)
        {
            auto argType = argTypes[i];
            if(args.GetSize() <= i)
            {
                ctx->Push(0);
                continue;
            }
            switch(argType)
            {
            case alt::INative::Type::ARG_BOOL:
                ctx->Push((bool)args[i]);
                break;
            case alt::INative::Type::ARG_INT32:
                ctx->Push((int32_t)args[i]);
                break;
            case alt::INative::Type::ARG_UINT32:
                ctx->Push((uint32_t)args[i]);
                break;
            case alt::INative::Type::ARG_FLOAT:
                ctx->Push((float*)args[i]);
                break;
            case alt::INative::Type::ARG_STRING:
                ctx->Push((char*)args[i]);
                break;
            default:
                //Log::Error << "Unsupported native arg type " << (int)argType << Log::Endl;
                break;
            }
        }

        bool success = native->Invoke(ctx);
        if(!success) Log::Error << "Error while calling native " << native->GetName().CStr() << Log::Endl;
    }
};
#endif
