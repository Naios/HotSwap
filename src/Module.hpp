
#ifndef Module_hpp_
#define Module_hpp_

#include <string>

template <class T>
class Module
{
public:
    std::string const& GetName() const;

    std::string test()
    {
        return "hey";
    }
};

#endif Module_hpp_
