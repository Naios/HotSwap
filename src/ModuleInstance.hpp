
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

    std::string _name, _type, _version;

    std::type_info const& _typeid;

public:
    ModuleInstance(ModuleInterface* ptr, std::string const& type, std::string const& name, std::string const& version = "")
        : _ptr(ptr), _type(type), _name(name), _version(version), _typeid(typeid(*ptr)) { }

    ModuleInstance(ModuleInstance const&) = delete;

    ModuleInstance(ModuleInstance&&) = delete;

    ModuleInstance& operator=(ModuleInstance const&) = delete;

    ModuleInstance& operator=(ModuleInstance&&) = delete;

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
    std::shared_ptr<T> GetInterface() const
    {
        static_assert(std::is_convertible<T, ModuleInterface>::value,
            "Can't cast to interfaces which are not a child of ModuleInterface!");

        if (!IsInstanceOf<T>())
           throw std::bad_cast("Tried to cast to wrong interface!");

        return std::dynamic_pointer_cast<T>(_ptr);
    }
};


typedef std::function<ModuleInstance*()> CreateModuleFn;

static std::string const CreateModuleFnName = "CreateModule";

template<typename _RTy>
struct unwrap_function;

template<typename _RTy, typename... _ATy>
struct unwrap_function < _RTy(_ATy...) >
{
    typedef _RTy return_type;

    typedef std::tuple<_ATy...> argument_type;

    typedef std::function<_RTy(_ATy...)> function_type;

    typedef _RTy(*function_ptr)(_ATy...);
};

template<typename _RTy, typename... _ATy>
struct unwrap_function < std::function<_RTy(_ATy...)> >
{
    typedef _RTy return_type;

    typedef std::tuple<_ATy...> argument_type;

    typedef std::function<_RTy(_ATy...)> function_type;

    typedef _RTy(*function_ptr)(_ATy...);
};

#endif // Module_hpp_
