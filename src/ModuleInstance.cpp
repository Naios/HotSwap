
#include <iostream>

#include "ModuleInstance.hpp"

template<typename _RTy>
struct unwrap_function;

template<typename _RTy, typename... _ATy>
struct unwrap_function < std::function<_RTy(_ATy...)> >
{
    typedef _RTy(*function_ptr)(_ATy...);
};

Module ModuleTemplateInstance::CreateInstance() const
{
    return Module(new ModuleInstance(shared_from_this(), _function()));
}

#ifdef _WIN32
// Windows

#include <windows.h>

std::string const& ModuleTemplateInstance::GetPlatformSpecificExtension()
{
    static std::string const extension = "dll";
    return extension;
}

boost::optional<ModuleTemplate> ModuleTemplateInstance::CreateFromPath(std::string const& path)
{
    HMODULE syshandle = LoadLibrary(path.c_str());
    if (!syshandle)
        return boost::none;

    ModuleCreateFunction const function =
        (unwrap_function<ModuleCreateFunction>::function_ptr)GetProcAddress(syshandle, CREATE_MODULE_FUNCTION_NAME);

    if (!function)
        return boost::none;

    return boost::make_optional(ModuleTemplate(
        new ModuleTemplateInstance(InternalHandleType(syshandle, [](void* handle)
        {
            FreeLibrary((HMODULE)handle);
        }),
        function)));
}

#else
// Posix


std::string const& ModuleTemplateInstance::GetPlatformSpecificExtension()
{
    static std::string const extension = "so";
    return extension;
}

boost::optional<ModuleTemplate> ModuleTemplateInstance::CreateFromPath(std::string const& path)
{
    // TODO
    return boost::make_optional(nullptr);
}

#endif
