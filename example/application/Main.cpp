
#include <iostream>

#include "Module.hpp"
#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"

#include <boost/filesystem/path.hpp>

int main(int argc, char** argv)
{
    std::cout << "Hot Swap example application..." << std::endl;

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
            std::cout << instance->GetInterface<Example>()->GetHey() << std::endl;

        std::cout << "Used " << ref.use_count() << std::endl;
    }
    else
    {
        std::cout << "ModuleTemplateInstance::CreateFromPath(name) errored! Used " << name << std::endl;
        return 1;
    }

    return 0;
}
