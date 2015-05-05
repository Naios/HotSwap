
#ifdef _WIN32
    #include <windows.h>
#else // Posix
    #include <dlfcn.h>
#endif

#include "Module.hpp"

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

std::string const& ModuleTemplateInstance::GetPlatformSpecificExtension()
{
    #ifdef _WIN32
        static std::string const extension = "dll";
    #else // Posix
        static std::string const extension = "so";
    #endif

    return extension;
}

boost::optional<ModuleTemplate> ModuleTemplateInstance::CreateFromPath(boost::filesystem::path const& path)
{
    #ifdef _WIN32
        HMODULE syshandle = LoadLibrary(path.generic_string().c_str());
    #else // Posix
        void* syshandle = dlopen(path.generic_string().c_str(), RTLD_LAZY);
    #endif

    if (!syshandle)
        return boost::none;

    InternalHandleType handle(syshandle, [](void* handle)
    {
        #ifdef _WIN32
            FreeLibrary((HMODULE)handle);
        #else // Posix
            dlclose(handle);
        #endif
    });

    #ifdef _WIN32
        unwrap_function<ModuleCreateFunction>::function_ptr const function =
            (unwrap_function<ModuleCreateFunction>::function_ptr)GetProcAddress(syshandle, CREATE_MODULE_FUNCTION_NAME);

    #else // Posix

        // Silences "warning: dereferencing type-punned pointer will break strict-aliasing rules" warnings according to:
        // http://en.wikipedia.org/wiki/Dynamic_loading
        union { unwrap_function<ModuleCreateFunction>::function_ptr function; void* raw; } alias;
        alias.raw = dlsym(syshandle, CREATE_MODULE_FUNCTION_NAME);
        unwrap_function<ModuleCreateFunction>::function_ptr function = alias.function;
    #endif

    if (!function)
        return boost::none;

    return boost::make_optional(ModuleTemplate(
        new ModuleTemplateInstance(std::move(handle), function)));
}
