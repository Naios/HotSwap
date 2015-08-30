
#ifndef ExampleSingleton_hpp_
#define ExampleSingleton_hpp_

#include "ModuleInterface.hpp"

#include "ExampleSingleton.hpp"

#include <mutex>
#include <iostream>

class Log
{
    int counter = 0;

public:
    void count()
    {
        ++counter;
        std::cout << "Count " << counter << std::endl;
    }
};

MODULE_EXPORT Log* GetLogSingleton();

#endif // ExampleSingleton_hpp_
