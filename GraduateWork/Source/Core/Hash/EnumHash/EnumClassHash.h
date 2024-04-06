#pragma once

struct EnumClassHash
{
public:
    template <typename Type>
    std::size_t operator()(Type Enum) const
    {
        return static_cast<std::size_t>(Enum);
    }
};
