
#include <iostream>

#include <boost/filesystem.hpp>

#include "ModuleInstance.hpp"
#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"
#include "ModulePlatformUtils.hpp"

int main(int argc, char** argv)
{
    boost::filesystem::path module_path("MyModule.dll");

    if (auto const lib = ModulePlatformUtils::LoadDynamicLibrary(module_path))
    {
        if (auto const function = ModulePlatformUtils::GetModuleFactoryFn(*lib))
        {
            std::unique_ptr<ModuleInstance> module((*function)());

            try
            {
                if (module->IsInstanceOf<Example>())
                    std::cout << "Is Example interface!" << std::endl;
                else
                    std::cout << "Is unknown interface!" << std::endl;

                std::cout << module->GetTypeId() << std::endl;

                std::cout << module->GetName() << std::endl;

                std::cout << module->GetInterface<Example>()->GetHey() << std::endl;
            }
            catch (std::bad_cast& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else
            std::cout << "function not found!";

        // No need to unload it, shared ptrs will take care of this.
        // ModulePlatformUtils::UnloadDynamicLibrary(*lib);
    }
    else
        std::cout << "could not load library";

    return 0;
}
