
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
    __declspec(dllexport) ModuleInstance* __cdecl CreateModule()
    {
        return new ModuleInstance("TC:Script", "Some scripts", "", new OtherExample());
    }
}
