#include "main.h"

EXPORT alt::IScriptRuntime* CreateScriptRuntime(alt::ICore* core)
{
    alt::ICore::SetInstance(core);
    auto runtime = new ConfigRuntime();
    return runtime;
}

EXPORT const char* GetType()
{
    return "config";
}

EXPORT uint32_t GetSDKVersion()
{
    return alt::ICore::SDK_VERSION;
}
