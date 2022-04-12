#pragma once
#include "scenario_evaluator.h"

class IKScenarioEvaluator : public ScenarioEvaluator, public Singleton<IKScenarioEvaluator>
{
public:
    void SetParticipants(Army* armyA, Army* armyB) override;
    void RunScenario(BattleScenario scenario) override;
};


