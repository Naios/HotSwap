
#include "ModuleInstance.hpp"

#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"

class OtherExample : public Example
{
    std::string GetHey()
    {
        Log::instance().count();
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

extern "C"
{
    MODULE_EXPORT ModuleInterface* CreateModule()
    {
        return new OtherExample();
    }
}
