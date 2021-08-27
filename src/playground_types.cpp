#include "playground_types.h"

int March::CalcUnitedTroopsNum() const
{
    int totalTroops = 0;
    for (int i = 0; i < RuntimeUnitPosition::bupNUM; ++i)
    {
        totalTroops += mNumTroops[i];
    }

    return totalTroops;
}