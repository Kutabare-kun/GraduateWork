#pragma once
#include "../../Allocator/ResourceAllocator.h"
#include "../../Resource/Font/FontResource.h"

class TimerManager;
class Raycast;
class ObjectCollection;

struct SharedContext
{
public:
    ObjectCollection* Objects;
    ResourceAllocator<TextureResource>* TextureAllocator;
    ResourceAllocator<FontResource>* FontAllocator;
    Raycast* RaycastSys;
    TimerManager* TimerManagerSys;
};
