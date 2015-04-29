
#ifndef ExampleModule_hpp_
#define ExampleModule_hpp_

#include "ModuleInstance.hpp"

class Example
{
public:
    virtual std::string GetHey()
    {
        return "hey";
    }
};

#endif // ExampleModule_hpp_
