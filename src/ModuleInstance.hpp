
#ifndef Module_hpp_
#define Module_hpp_

#include <string>
#include <memory>

class ModuleInstance
{
    std::shared_ptr<void> _ptr;

    std::string const _name, _type, _version;

public:
    ModuleInstance(std::string const& type, std::string const& name, std::string const& version, void* ptr)
        : _ptr(ptr), _name(name), _type(type), _version(version) { }

    std::string const& GetName() const
    {
        return _name;
    }

    std::string const& GetType() const
    {
        return _type;
    }

    template <class T>
    T* GetInterface() const
    {
        return static_cast<T*>(_ptr.get());
    }

    std::string test()
    {
        return "hey";
    }
};

#endif // Module_hpp_
