#include "ik_army_provider.h"
#include "ik_scenario_evaluator.h"
#include "ik_analytics.h"

int main()
{
    IKDummyArmyProvider::CreateInst();
    IKScenarioEvaluator::CreateInst();

    IKScenarioEvaluator::Inst()->SetParticipants(IKDummyArmyProvider::Inst()->GetArmy(BattleSide::SideA), 
                                                 IKDummyArmyProvider::Inst()->GetArmy(BattleSide::SideB));
    IKScenarioEvaluator::Inst()->RunScenario(BattleScenario::SingleBattle);
        
    return 0;
}