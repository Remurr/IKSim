#pragma once
#include "army_provider.h"

class IKDummyArmyProvider : public ArmyProvider, public Singleton<IKDummyArmyProvider>
{
public:    
    std::unique_ptr<Army> GetArmy(BattleSide side) override;
};