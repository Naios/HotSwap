
#ifndef ExampleSingleton_hpp_
#define ExampleSingleton_hpp_

#include "Module.hpp"

#include <mutex>
#include <iostream>

class Log
{
    int counter = 0;

public:
    static Log& instance()
    {
        static Log log;
        std::cout << "Log created" << std::endl;
        return log;
    }

    void count()
    {
        ++counter;
        std::cout << "Count " << counter << std::endl;
    }
};

#endif // ExampleSingleton_hpp_
