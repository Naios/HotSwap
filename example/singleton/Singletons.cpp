
#define DLL_EXPORT 1

#include "ModuleInterface.hpp"

#include "ExampleSingleton.hpp"

#include <iostream>

void ObjectMgr::print()
{
    std::cout << "Object: " << i++ << std::endl;
}

MODULE_EXPORT Log* GetLogSingleton()
{
    static Log log;
    return &log;
}
