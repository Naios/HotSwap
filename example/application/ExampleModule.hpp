
#ifndef ExampleModule_hpp_
#define ExampleModule_hpp_

#include <string>

#include "ModuleInterface.hpp"

class UnitAI
{
public:
    virtual ~UnitAI() { }

    virtual void Greet() = 0;
};

class Example : public ModuleInterface
{
public:
    virtual ~Example() { }

    virtual std::string GetHey()
    {
        return "hey";
    }

    virtual UnitAI* create() = 0;
};

class BadExample : public ModuleInterface
{
public:
    virtual ~BadExample() { }

    virtual std::string GetHey()
    {
        return "Bad Example!";
    }
};

#endif // ExampleModule_hpp_
