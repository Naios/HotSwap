
#include "Module.hpp"

#include "ExampleModule.hpp"

class OtherExample : public Example
{
    std::string GetHey() override
    {
        return "huhu from overwritten!";
    }
};

extern "C"
{
    __declspec(dllexport) Module* __cdecl CreateModule()
    {
        return new Module("TC:Script", "Some scripts", "", new OtherExample());
    }
}
