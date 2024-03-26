#pragma once
#include <string>

template<typename Derived, typename Product>
class BaseResource
{
public:
    virtual ~BaseResource() = default;
    
    virtual bool LoadFromFile(const std::string& FilePath)
    {
        return false;
    }

    Product& Get()
    {
        return static_cast<Derived*>(this)->Get_Impl();
    }
};