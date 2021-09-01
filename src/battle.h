#pragma once

#include "runtime_types.h"

class Battle
{
public:
    Battle();
    Battle(March* marchA, March* marchB);

    void AddParticipant(AttackSide pt, March* march);

    void Execute();
    
    const Report* GetReport() const { return &mReport; }

private:
    void PreBattle();
    void PostBattle();

    bool FindTargets();
    bool MoveTroops();
    void MakeDamage();
    void EnergyRegen();

    int  AutoAttack(RuntimeUnit &actor);

private:
    Report       mReport;
    RuntimeMarch mRuntimeMarches[AttackSide::asNUM];
    int          mBattleFrameNum;

    March* mMarches[AttackSide::asNUM];
};

// TODO move to separate file
class BaseBuff
{

};

class BaseSkill
{

};
