#pragma once
#include <stdio.h>
#include "runtime_types.h"

class Analyzer
{
public:
    // Don't like that naming, think something different
    static void Analyze(const Report* rep)
    {
        Log::Print("\nTest Battle: %s", rep->mResult == BattleResult::brVictory ? "VICTORY" : "DEFEAT");
        Log::Print("\nSurvived\t%d\t-\t%d", rep->mLosses[AttackSide::asAtk].numSurvived,  rep->mLosses[AttackSide::asDef].numSurvived);
        Log::Print("\nDead    \t%d\t-\t%d", rep->mLosses[AttackSide::asAtk].numDead,      rep->mLosses[AttackSide::asDef].numDead);
        Log::Print("\nWoundedL\t%d\t-\t%d", rep->mLosses[AttackSide::asAtk].woundedLight, rep->mLosses[AttackSide::asDef].woundedLight);
        Log::Print("\nWoundedH\t%d\t-\t%d", rep->mLosses[AttackSide::asAtk].woundedHeavy, rep->mLosses[AttackSide::asDef].woundedHeavy);
        Log::Print("\n\n");
    }
};