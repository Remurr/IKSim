#pragma once
#include <vector>

#include "types.h"

class Battle
{
public:
    Battle() {}
    Battle(March* marchA, March* marchB);

    void AddParticipant(AttackSide pt, March* march);

    void Execute();
    
    const Report* GetReport() const { return &mReport; }

private:
    void PreBattle();

    bool FindTargets();
    bool MoveTroops();
    void MakeDamage();

    int  AutoAttack(BattleUnit &actor);

private:
    Report       mReport;
    RuntimeMarch mRuntimeMarches[AttackSide::asNUM];
    int          mFrames;

    March* mMarches[AttackSide::asNUM];
};

// TODO move to separate file
class BaseBuff
{

};

class BaseSkill
{

};
