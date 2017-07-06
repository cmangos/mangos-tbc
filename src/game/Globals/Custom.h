#pragma once

#include "Common.h"
#include "Singleton.h"

class Custom : public CSingleton<Custom>
{
public:
    Custom();
    ~Custom();
};

#define sCustom Custom::Instance()
