
#define DECL_IN_MODULE 1

#include "ModuleInterface.hpp"

#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"
#include "MyDependency.hpp"

class MyAI : public UnitAI
{
public:
    virtual ~MyAI()
    {
        PRINT_MY_DEPENDENCY_COUNTER;

        std::cout << "Destroy ~MyAI" << std::endl;
    }

    void Greet() override
    {
        ObjectMgr::instance()->print();

        PRINT_MY_DEPENDENCY_COUNTER;

        std::cout << "Greetings from MyAI" << std::endl;
    }
};

class OtherExample : public Example
{
public:
    virtual ~OtherExample()
    {
        std::cout << "Destroy ~OtherExample" << std::endl;
    }

    std::string GetHey()
    {
        ObjectMgr::instance()->print();
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

    UnitAI* create() override
    {
        return new MyAI();
    }
};

DEFINE_MODULE(OtherExample)
