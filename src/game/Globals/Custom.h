#pragma once

#include "Common.h"
#include "Singleton.h"

enum MessageTypes;

class Custom : public CSingleton<Custom>
{
public:
    Custom();
    ~Custom();
};

#define sCustom Custom::Instance()
