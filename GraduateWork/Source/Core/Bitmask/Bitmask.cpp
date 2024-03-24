#include "Bitmask.h"

Bitmask::Bitmask()
    : Bits(0)
{}

void Bitmask::SetMask(Bitmask& Other)
{
    Bits = Other.GetMask();
}

uint32_t Bitmask::GetMask() const
{
    return Bits;
}

bool Bitmask::GetBit(int Position) const
{
    return (Bits & (1 << Position)) != 0;
}

// A simple helper method that calls set or clear bit
void Bitmask::SetBit(int Position, bool State)
{
    if(State)   SetBit(Position);
    else        ClearBit(Position);
}

void Bitmask::SetBit(int Position)
{
    Bits = Bits | 1 << Position;
}

void Bitmask::ClearBit(int Position)
{
    Bits = Bits & ~(1 << Position);
}

void Bitmask::Clear()
{
    Bits = 0;
}