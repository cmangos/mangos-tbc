#pragma once

template<class T>
class CSingleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }
};

template <class X>
X& FSingleton()
{
    static X x;
    return x;
}