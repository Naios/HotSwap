
#define DLL_EXPORT 1

#include "ModuleInterface.hpp"

#include "ExampleSingleton.hpp"

#include <iostream>

#include "MyDependency.hpp"

void ObjectMgr::print()
{
    std::cout << "Object: " << i++ << std::endl;

    PRINT_MY_DEPENDENCY_COUNTER;
}

MODULE_EXPORT Log* GetLogSingleton()
{
    static Log log;
    return &log;
}
