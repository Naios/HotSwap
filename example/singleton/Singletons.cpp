
#define DLL_EXPORT 1

#include "ModuleInterface.hpp"

#include "ExampleSingleton.hpp"

MODULE_EXPORT Log* GetLogSingleton()
{
    static Log log;
    return &log;
}
