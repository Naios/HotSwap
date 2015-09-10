
#ifndef ExampleSingleton_hpp_
#define ExampleSingleton_hpp_

#include "ModuleInterface.hpp"

#include "ExampleSingleton.hpp"

#include <mutex>
#include <iostream>

class Log
{
    int counter = 0;

public:
    void count()
    {
        ++counter;
        std::cout << "Count " << counter << std::endl;
    }
};

template<typename T>
class Singleton
{
public:
    Singleton() = default;
    Singleton(Singleton const&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator= (Singleton const&) = delete;
    Singleton& operator= (Singleton&&) = delete;

    static T* instance()
    {
        static T _instance;
        return &_instance;
    }
};

class MODULE_EXPORT ObjectMgr
{
    int i;

public:
    ObjectMgr() : i(0) { }
    ObjectMgr(ObjectMgr const&) = delete;
    ObjectMgr(ObjectMgr&&) = delete;
    ObjectMgr& operator= (ObjectMgr const&) = delete;
    ObjectMgr& operator= (ObjectMgr&&) = delete;

    static ObjectMgr* instance()
    {
        static ObjectMgr _instance;
        return &_instance;
    }

    void print();
};

MODULE_EXPORT Log* GetLogSingleton();

#endif // ExampleSingleton_hpp_
