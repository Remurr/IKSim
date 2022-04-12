#include "ik_army_provider.h"

std::unique_ptr<Army> IKDummyArmyProvider::GetArmy(BattleSide side)
{
    return std::make_unique<Army>();
}