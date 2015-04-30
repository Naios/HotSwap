
#include "ModuleInstance.hpp"

#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"

class OtherExample : public Example
{
    std::string GetHey() override
    {
        Log::instance().count();
        return "huhu from overwritten!";
    }
};

extern "C"
{
    MODULE_EXPORT ModuleInstance* CreateModule()
    {
        return new ModuleInstance(new OtherExample(), "TC:Script", "Some scripts", "");
    }
}
