#pragma once

#include "cpp-sdk/SDK.h"

class ConfigResource;
class ConfigRuntime : public alt::IScriptRuntime
{
public:
    ConfigRuntime() {};
    alt::IResource::Impl* CreateImpl(alt::IResource* resource) override;
    void DestroyImpl(alt::IResource::Impl* impl) override;

    static ConfigRuntime& Instance()
	{
		static ConfigRuntime _instance;
		return _instance;
	}
};