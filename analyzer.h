#pragma once
#include <stdio.h>

#include "types.h"

class Analyzer
{
public:
    // Don't like that naming, think something different
    static void Analyze(const Report* rep)
    {
        printf("\nTest Battle: %s", rep->mResult == BattleResult::brVictory ? "VICTORY" : "DEFEAT");
        printf("\nSurvived\t%d\t-\t%d", rep->mLosses[AttackSide::asAtk].numSurvived,  rep->mLosses[AttackSide::asDef].numSurvived);
        printf("\nDead    \t%d\t-\t%d", rep->mLosses[AttackSide::asAtk].numDead,      rep->mLosses[AttackSide::asDef].numDead);
        printf("\nWoundedL\t%d\t-\t%d", rep->mLosses[AttackSide::asAtk].woundedLight, rep->mLosses[AttackSide::asDef].woundedLight);
        printf("\nWoundedH\t%d\t-\t%d", rep->mLosses[AttackSide::asAtk].woundedHeavy, rep->mLosses[AttackSide::asDef].woundedHeavy);
        printf("\n\n");
    }
};