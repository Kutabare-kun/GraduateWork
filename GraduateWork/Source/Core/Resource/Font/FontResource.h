#pragma once
#include <raylib.h>

#include "../Base/BaseResource.h"

class FontResource
    : public BaseResource<FontResource, Font>
{
public:
    ~FontResource() override;
    
    bool LoadFromFile(const std::string& FilePath) override;

    Font Get_Impl();

private:
    Font TextFont;
};
