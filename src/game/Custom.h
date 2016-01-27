#pragma once

#include "Singleton.h"

class Custom : public Singleton<Custom>
{
public:
    Custom();
    ~Custom();

    uint32 GetAutoItemPrice(uint32 itemid);
private:
};

#define sCustom Custom::Instance()
