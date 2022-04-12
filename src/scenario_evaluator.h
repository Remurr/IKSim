#pragma once
#include "army_provider.h"

enum class BattleScenario
{
    SingleBattle,
};

class ScenarioEvaluator
{
    // This class is used to implement various scenarios of making battles
    // Single battle, series of battles to find average, variation of some parameter to see its input etc
public:
    virtual void SetParticipants(Army* armyA, Army* armyB) = 0;
    virtual void RunScenario(BattleScenario scenario) = 0;
};
