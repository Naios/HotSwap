
#ifndef ExampleDependency_hpp_
#define ExampleDependency_hpp_

#include "ModuleInterface.hpp"

#include <iostream>

#ifdef DLL_EXPORT_MY_DEPENDENCY
#define MY_DEPENDENCY_MODULE_EXPORT DECL_EXPORT
#else
#define MY_DEPENDENCY_MODULE_EXPORT DECL_IMPORT 
#endif

MY_DEPENDENCY_MODULE_EXPORT extern int dependency_counter_int;

#define PRINT_MY_DEPENDENCY_COUNTER std::cout << "dependency_counter_int = " << dependency_counter_int++ << std::endl

#endif // ExampleDependency_hpp_
