#pragma once
#include "enums.h"

class IBuff
{
public:
    virtual ~IBuff() = 0 {}
};

class BuffEnergyRegen : public IBuff
{
public:
    void Init(float value, float duration) {}
};

// TBD
class VIPBuffs
{
    int mVIPLvl;
};

// TBD
struct StatBuff
{

};

// TBD
class ConsumableBuffs
{
};
