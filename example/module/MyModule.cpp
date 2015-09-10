
#define DECL_IN_MODULE 1

#include "ModuleInterface.hpp"

#include "ExampleModule.hpp"
#include "ExampleSingleton.hpp"

class MyAI : public UnitAI
{
public:
    virtual ~MyAI()
    {
        std::cout << "Destroy ~MyAI" << std::endl;
    }

    void Greet() override
    {
        ObjectMgr::instance()->print();
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
