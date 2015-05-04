
#ifndef ExampleModule_hpp_
#define ExampleModule_hpp_

#include <string>

#include "ModuleInterface.hpp"

class Example : public ModuleInterface
{
public:
    virtual std::string GetHey()
    {
        return "hey";
    }
};

class BadExample : public ModuleInterface
{
public:
    virtual std::string GetHey()
    {
        return "Bad Example!";
    }
};

#endif // ExampleModule_hpp_
