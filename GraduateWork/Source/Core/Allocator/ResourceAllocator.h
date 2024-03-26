#pragma once
#include <map>
#include <memory>
#include <string>

#include "../Resource/Texture/TextureResource.h"

template<typename Type>
class ResourceAllocator
{    
public:
    int Add(const std::string& FilePath)
    {
        auto Iter = Resources.find(FilePath);
        if (Iter != Resources.end())
        {
            return Iter->second.first;
        }

        std::shared_ptr<Type> Resource = std::make_shared<Type>();
        if (!Resource->LoadFromFile(FilePath))
        {
            return -1;
        }

        Resources.insert(std::make_pair(FilePath, std::make_pair(CurrentId, Resource)));
        
        return CurrentId++;
    }

    void Remove(int Id)
    {
        for (auto Iter = Resources.begin(); Iter != Resources.end(); ++Iter)
            if (Iter->second.first == Id)
                Resources.erase(Iter->first);
    }

    std::shared_ptr<Type> Get(int Id)
    {
        for (auto Iter = Resources.begin(); Iter != Resources.end(); ++Iter)
            if (Iter->second.first == Id)
                return Iter->second.second;

        return nullptr;
    }

    bool Has(int Id)
    {
        return Get(Id) != nullptr;
    }
    
private:
    int CurrentId{};
    std::map<std::string, std::pair<int, std::shared_ptr<Type>>> Resources;
};
