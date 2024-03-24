#pragma once
#include <cstdint>

class Bitmask
{
public:
    Bitmask();
    
    // Overwrites this bitmask.
    void SetMask(Bitmask& Other); 
	
    // Returns binary representation of bitmask.
    uint32_t GetMask() const; 
    
    // Returns true if bit at pos = 1, else false.
    bool GetBit(int Position) const; 
   
    // Sets bit at specified pos to 1 or 0 (true or false).
    void SetBit(int Position, bool State);
	
    // Sets bit at pos to 1.
    void SetBit(int Position); 
	
    // Sets bit at pos to 0.
    void ClearBit(int Position);
    
    // Sets all bits to 0.
    void Clear(); 
    
private:
    uint32_t Bits;
};
