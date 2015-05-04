
#ifndef ModuleInterface_hpp_
#define ModuleInterface_hpp_

#if defined(_MSC_VER)
    //  Microsoft
    #define MODULE_EXPORT __declspec(dllexport)
#elif defined(_GCC)
    //  GCC
    #define MODULE_EXPORT __attribute__((visibility("default")))
#else
    #define MODULE_EXPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

// Module interface base class
// Ensures that there are runtime infos generated for our child classes.
class ModuleInterface
{
public:
    virtual ~ModuleInterface() { }
};

#endif // ModuleInterface_hpp_
