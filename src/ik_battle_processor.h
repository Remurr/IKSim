#pragma once
#include "battle_processor.h"

class IKBattleProcessor : public BattleProcessor, public Singleton<IKBattleProcessor>
{
    std::unique_ptr<Report> Process(Army* armyA, Army* armyB) override;
};
