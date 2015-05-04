
#ifndef Module_hpp_
#define Module_hpp_

#include <string>
#include <memory>
#include <exception>
#include <typeinfo>
#include <type_traits>
#include <utility>

#include <boost/optional.hpp>
// #include <boost/filesystem.hpp>

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

class ModuleInstance;
class ModuleTemplateInstance;

typedef std::shared_ptr<ModuleInstance const> Module;
typedef std::shared_ptr<ModuleTemplateInstance const> ModuleTemplate;

class ModuleInstance
    : public std::enable_shared_from_this<ModuleInstance>
{
    friend class ModuleTemplateInstance;

    std::shared_ptr<ModuleInterface> const _interface;

    ModuleTemplate const _moduleTemplate;

    ModuleInstance(ModuleTemplate const moduleTemplate, ModuleInterface* moduleInterface) :
        _moduleTemplate(moduleTemplate), _interface(moduleInterface) { }

public:
    ModuleInstance(ModuleInstance const&) = delete;
    ModuleInstance(ModuleInstance&&) = delete;
    ModuleInstance& operator= (ModuleInstance const&) = delete;
    ModuleInstance& operator= (ModuleInstance&&) = delete;

    // Returns true if the interface is of type T
    template <class T>
    inline bool IsInstanceOf() const
    {
        static_assert(std::is_convertible<T, ModuleInterface>::value,
            "Parameter T needs to be child class of ModuleInterface!");

        return (dynamic_cast<T*>(_interface.get()) != nullptr);
    }

    // Throws std::bad_cast exception on bad casts.
    template <class T>
    std::shared_ptr<T> GetInterface() const
    {
        static_assert(std::is_convertible<T, ModuleInterface>::value,
            "Can't cast to interfaces which are not a child of ModuleInterface!");

        if (!IsInstanceOf<T>())
           throw std::bad_cast();

        return std::dynamic_pointer_cast<T>(_interface);
    }
};

typedef std::function<ModuleInterface*()> ModuleCreateFunction;

static char const* const CREATE_MODULE_FUNCTION_NAME = "CreateModule";

class ModuleTemplateInstance
    : public std::enable_shared_from_this<ModuleTemplateInstance>
{
    typedef std::unique_ptr<void, void(*)(void*)> InternalHandleType;

    InternalHandleType const _handle;

    ModuleCreateFunction const _function;

    ModuleTemplateInstance(InternalHandleType&& handle, ModuleCreateFunction const& function)
        : _handle(std::forward<InternalHandleType>(handle)), _function(function) { }

public:
    ~ModuleTemplateInstance() { }

    ModuleTemplateInstance(ModuleTemplateInstance const&) = delete;
    ModuleTemplateInstance(ModuleTemplateInstance&&) = delete;
    ModuleTemplateInstance& operator= (ModuleTemplateInstance const&) = delete;
    ModuleTemplateInstance& operator= (ModuleTemplateInstance&&) = delete;

    // Try to create a new module template from the given path.
    // Returns an non empty optional on success.
    static boost::optional<ModuleTemplate> CreateFromPath(std::string const& path);

    // Returns "dll" on windows or "so" on posix.
    static std::string const& GetPlatformSpecificExtension();

    // Create a new instance of the module.
    Module CreateInstance() const;
};

#endif // Module_hpp_
