#pragma once

struct ComponentPairHash
{
    template <typename Type>
    std::size_t operator()(Type Pair) const
    {
        std::size_t X = Pair.first->GetOwner()->GetInstanceID()->GetID();
        std::size_t Y = Pair.second->GetOwner()->GetInstanceID()->GetID();

        return (X >= Y) ? (X * X + X + Y) : (Y * Y + Y + X);
    }
};
