
#include <iostream>

// #include <boost/filesystem.hpp>

#include "ModuleInstance.hpp"
#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"

int main(int argc, char** argv)
{
    #ifdef _WIN32
        std::string const name = "MyModule.dll";
    #else // Posix
        std::string const name = "libMyModule.so";
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

    return 0;
}
