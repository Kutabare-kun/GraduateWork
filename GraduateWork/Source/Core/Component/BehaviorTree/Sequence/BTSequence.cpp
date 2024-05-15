#include "BTSequence.h"

bool BTSequence::Run()
{
    for (const auto& Child : GetChildren())
    {
        if (Child->Run()) continue;
        return false;
    }

    return true;
}
