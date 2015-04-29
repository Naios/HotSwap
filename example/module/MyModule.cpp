
#include "Module.hpp"

#include "ExampleModule.hpp"

extern "C"
{
    __declspec(dllexport) ExampleModule __cdecl CreateModule()
    {
        return ExampleModule();
    }
}
