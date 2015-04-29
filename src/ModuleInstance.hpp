
#ifndef Module_hpp_
#define Module_hpp_

#include <string>
#include <memory>
#include <exception>
#include <typeinfo>
#include <type_traits>

#include <boost/optional.hpp>

#if defined(_MSC_VER)
    //  Microsoft
    #define MODULE_EXPORT __declspec(dllexport)
#elif defined(_GCC)
    //  GCC
    #define MODULE_EXPORT __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define MODULE_EXPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

// Module interface base class
// Ensures that there are runtime infos generated for our child classes.
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
    bool IsInstanceOf() const
    {
        static_assert(std::is_convertible<T, ModuleInterface>::value,
            "Parameter T needs to be child class of ModuleInterface!");
        return (dynamic_cast<T*>(_ptr.get()) != nullptr);
    }

    // Throws std::bad_cast exception on bad casts.
    template <class T>
    T* GetInterface() const
    {
        static_assert(std::is_convertible<T, ModuleInterface>::value,
            "Can't cast to interfaces which are not a child of ModuleInterface!");

        T* ptr = dynamic_cast<T*>(_ptr.get());
        if (ptr == nullptr)
            throw std::bad_cast("Tried to cast to wrong interface!");
        else
            return ptr;
    }
};

#endif // Module_hpp_
