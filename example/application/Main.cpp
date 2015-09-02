
#include <iostream>

#include "Module.hpp"
#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"

#include <boost/filesystem.hpp>

int main(int argc, char** argv)
{
    std::cout << "Hot Swap example application..." << std::endl;

    GetLogSingleton()->count();

    #ifdef _WIN32
        std::string const name = "MyModule.dll";
    #else // Posix
        std::string const name = "./libMyModule.so";
    #endif

    if (auto const templ = ModuleTemplateInstance::CreateFromPath(name))
    {
        auto ref = *templ;

        Module instance = (*templ)->CreateInstance();
        if (!instance->IsInstanceOf<Example>())
            std::cout << "Not example interface!" << std::endl;
        else
        {
            std::cout << instance->GetInterface<Example>()->GetHey() << std::endl;

            std::cout << "Creating AI..." << std::endl;

            UnitAI* ai = instance->GetInterface<Example>()->create();

            ai->Greet();

            delete ai;

            std::cout << "deleted AI" << std::endl;
        }

        std::cout << "Used " << ref.use_count() << std::endl;
    }
    else
    {
        std::cout << "ModuleTemplateInstance::CreateFromPath(name) errored! Used " << name << std::endl;
        return 1;
    }

    std::cout << "unloaded" << std::endl;

    return 0;
}
