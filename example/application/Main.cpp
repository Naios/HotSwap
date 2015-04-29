
#include <iostream>

#include <boost/filesystem.hpp>

#include "Module.hpp"

#include "ExampleModule.hpp"

#include <windows.h>

typedef ExampleModule*(*CreateModule)();

int main(int argc, char** argv)
{
    CreateModule function;
    BOOL fFreeResult;

    HINSTANCE moduleHandle = LoadLibrary("MyModule.dll");

    if (moduleHandle)
    {
        function = (CreateModule) GetProcAddress(moduleHandle, "CreateModule");

        if (function != NULL)
            std::cout << (*function)()->test();
        else
            std::cout << "function not found!";

        fFreeResult = FreeLibrary(moduleHandle) ;
    }
    else
        std::cout << "could not load library";

    return 0;
}
