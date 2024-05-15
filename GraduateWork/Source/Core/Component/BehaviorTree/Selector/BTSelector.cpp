#include "BTSelector.h"

bool BTSelector::Run()
{
    for (const auto& Child : GetChildren())
    {
        if (!Child->Run()) continue;
        return true;
    }

    return false;
}
