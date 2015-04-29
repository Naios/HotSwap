
#ifndef Module_hpp_
#define Module_hpp_

#include <string>
#include <memory>
#include <exception>
#include <typeinfo>

#include <boost/optional.hpp>

class BadInterfaceCastException: public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Tried to cast to wrong interface!";
    }
};

class ModuleInterface
{
public:
    virtual ~ModuleInterface() { }
};

class ModuleInstance
{
    std::shared_ptr<ModuleInterface> _ptr;

    std::string const _name, _type, _version;

    std::type_info const& _typeid;

public:
    ModuleInstance(std::string const& type, std::string const& name, std::string const& version, ModuleInterface* ptr)
        : _ptr(ptr), _name(name), _type(type), _version(version), _typeid(typeid(*ptr)) { }

    std::string const& GetName() const
    {
        return _name;
    }

    std::string const& GetType() const
    {
        return _type;
    }

    std::string GetTypeId() const
    {
        return _typeid.name();
    }

    // Returns true if the interface is of type T
    template <class T>
    bool IsInterface() const
    {
        return (dynamic_cast<T*>(_ptr.get()) != nullptr);
    }

    // Throws BadInterfaceException on failure.
    template <class T>
    T* GetInterface() const
    {
        T* ptr = dynamic_cast<T*>(_ptr.get());
        if (ptr == nullptr)
            throw BadInterfaceCastException();
        else
            return ptr;
    }

    std::string test()
    {
        return "hey";
    }
};

#endif // Module_hpp_
