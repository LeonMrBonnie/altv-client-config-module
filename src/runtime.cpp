#include "runtime.h"
#include "resource.h"
#include "parser/parser.h"

alt::IResource::Impl* ConfigRuntime::CreateImpl(alt::IResource* impl)
{
    auto resource = new ConfigResource(this, impl);
    return resource;
}

void ConfigRuntime::DestroyImpl(alt::IResource::Impl* impl)
{
    ConfigResource* resource = dynamic_cast<ConfigResource*>(impl);
    if(resource != nullptr) 
    {
        delete resource;
    }
}
