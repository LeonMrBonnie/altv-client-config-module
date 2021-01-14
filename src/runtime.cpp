#include "runtime.h"
#include "resource.h"

alt::IResource::Impl* ConfigRuntime::CreateImpl(alt::IResource* impl)
{
    auto resource = new ConfigResource(this, impl);
    //resources.emplace(&resource);
    return resource;
}

void ConfigRuntime::DestroyImpl(alt::IResource::Impl* impl)
{
    ConfigResource* resource = dynamic_cast<ConfigResource*>(impl);
    if(resource != nullptr) 
    {
        //resources.erase(resource);
        delete resource;
    }
}