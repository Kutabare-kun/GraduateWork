#pragma once
#include "../../Allocator/ResourceAllocator.h"

class TimerManager;
class Raycast;
class ObjectCollection;

struct SharedContext
{
public:
    ObjectCollection* Objects;
    ResourceAllocator<TextureResource>* TextureAllocator;
    Raycast* RaycastSys;
    TimerManager* TimerManagerSys;
};
