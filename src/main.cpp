#include "main.h"
#include "Log.h"

#define MODULE_TYPE "config"

#ifdef CLIENT_MODULE
EXPORT alt::IScriptRuntime* CreateScriptRuntime(alt::ICore* core)
{
    alt::ICore::SetInstance(core);
    auto runtime = &ConfigRuntime::Instance();
    
    return runtime;
}

EXPORT const char* GetType()
{
    return MODULE_TYPE;
}
#endif

#ifdef SERVER_MODULE
EXPORT bool altMain(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    auto& runtime = ConfigRuntime::Instance();
    core->RegisterScriptRuntime(MODULE_TYPE, &runtime);
    Log::Colored << "Loaded Config module. Version ~y~v" MODULE_VERSION << Log::Endl;

    return true;
}
#endif

EXPORT uint32_t GetSDKVersion()
{
    return alt::ICore::SDK_VERSION;
}
