
#ifndef Module_Utils_hpp_
#define Module_Utils_hpp_

#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>

#include <memory>

#include "ModuleInstance.hpp"

typedef std::shared_ptr<void> DynamicLibraryRef;

class ModulePlatformUtils
{
public:
    static boost::optional<DynamicLibraryRef> LoadDynamicLibrary(boost::filesystem::path const& path);

    static boost::optional<CreateModuleFn> GetModuleFactoryFn(DynamicLibraryRef const handle);

    static bool UnloadDynamicLibrary(DynamicLibraryRef& handle);
};

#endif // Module_Utils_hpp_
