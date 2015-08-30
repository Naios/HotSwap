
#ifndef ModuleInterface_hpp_
#define ModuleInterface_hpp_

#if defined(_MSC_VER)
    //  Microsoft
    #define DECL_EXPORT __declspec(dllexport)
#elif defined(_GCC)
    //  GCC
    #define DECL_EXPORT __attribute__((visibility("default")))
#else
    #define DECL_EXPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#if defined(_MSC_VER)
//  Microsoft
#define DECL_IMPORT __declspec(dllimport)
#elif defined(_GCC)

#else

#endif

#ifdef DLL_EXPORT
#define MODULE_EXPORT DECL_EXPORT
#else
#define MODULE_EXPORT DECL_IMPORT 
#endif

// Module interface base class
// Ensures that there are runtime infos generated for our child classes.
class ModuleInterface
{
public:
    virtual ~ModuleInterface() { }
};

// Defines an exported module
#define DEFINE_MODULE(MODULE_NAME) \
    extern "C" \
    { \
        DECL_EXPORT ModuleInterface* CreateModule() \
        { \
            return new MODULE_NAME(); \
        } \
    }

#endif // ModuleInterface_hpp_
