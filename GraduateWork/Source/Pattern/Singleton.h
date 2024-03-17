#pragma once

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

template<typename Derived>
class Singleton : private NonCopyable
{
public:
    static Derived& GetInstance()
    {
        static Derived Instance;
        return Instance;
    }
    
protected:
    Singleton() = default;
};
