
#ifdef _WIN32

#include "ModulePlatformUtils.hpp"

#include <windows.h>

bool Unload(void* handle)
{
    return FreeLibrary((HMODULE)handle) != 0;
}

boost::optional<DynamicLibraryRef> ModulePlatformUtils::LoadDynamicLibrary(boost::filesystem::path const& path)
{
    if (DynamicLibraryRef const handle = DynamicLibraryRef(LoadLibrary(path.string().c_str()), Unload))
        return boost::make_optional(handle);
    else
        return boost::none;
}

boost::optional<CreateModuleFn> ModulePlatformUtils::GetModuleFactoryFn(DynamicLibraryRef const handle)
{
    if (auto const ptr = (unwrap_function<CreateModuleFn>::function_ptr)GetProcAddress((HMODULE)handle.get(), CreateModuleFnName.c_str()))
        return boost::make_optional(CreateModuleFn(ptr));
    else
        return boost::none;
}

bool ModulePlatformUtils::UnloadDynamicLibrary(DynamicLibraryRef& handle)
{
    bool const result = Unload(handle.get());
    handle.reset();
    return result;
}

#endif // _WIN32
