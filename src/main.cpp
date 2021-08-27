#include "playground.h"
#include "battle.h"
#include "analyzer.h"
#include "config.h"

int main()
{
    gConfig.Init();

    TestPlaygroundA testEnv;
    testEnv.Init();

    Battle battle;
    battle.AddParticipant(AttackSide::asAtk, testEnv.GetMarch(AttackSide::asAtk));
    battle.AddParticipant(AttackSide::asDef, testEnv.GetMarch(AttackSide::asDef));
    battle.Execute();
    
    const Report* rep = battle.GetReport();
    Analyzer::Analyze(rep);

    return 0;
}