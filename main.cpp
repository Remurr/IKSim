#include "environment.h"
#include "battle.h"
#include "analyzer.h"

int main()
{
    TestEnvironmentA testEnv;

    Battle battle;
    battle.AddParticipant(AttackSide::asAtk, testEnv.GetMarch(AttackSide::asAtk));
    battle.AddParticipant(AttackSide::asDef, testEnv.GetMarch(AttackSide::asDef));
    battle.Execute();
    
    const Report* rep = battle.GetReport();
    Analyzer::Analyze(rep);
    delete rep;

    return 0;
}