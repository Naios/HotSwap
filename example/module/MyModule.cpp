
#define DECL_IN_MODULE 1

#include "ModuleInterface.hpp"

#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"

class OtherExample : public Example
{
    std::string GetHey()
    {
        GetLogSingleton()->count();
        return "huhu from MyModule (it works)!";
    }

    std::string GetName() const
    {
        return "My example module";
    }

    std::string GetTypeId() const
    {
        return "My typeid";
    }
};

DEFINE_MODULE(OtherExample)
