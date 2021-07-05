#pragma once
#include <vector>

#include "types.h"

class BaseBuff
{

};

class BaseSkill
{

};

class Battle
{
public:
    Battle()
        : mReport(nullptr)
    {

    }

    void AddParticipant(AttackSide pt, March* march)
    {
        mMarches[pt].push_back(march);
    }

    void Execute()
    {
        mReport = new Report();

        // TODO
        // We start with very-very dummy approach when we kill 'atk' number of soldiers each turn
        // No buffs, no tech etc
    }

    const Report* GetReport() const { return mReport; }

private:
    Report *mReport;
    std::vector<March*> mMarches[AttackSide::asNUM];
};