#pragma once

template<class T1>
class Singleton
{
public:
    static T1& Instance()
    {
        static T1 instance;
        return instance;
    }
};
