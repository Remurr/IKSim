#pragma once
#include <vector>
#include <memory>

#include "common.h"
#include "army_provider.h"

struct ReplayAction
{
    // Single instance of making damage/using spell during battle
    BattleSide instigator;
};

struct Replay
{
    // List of events happened during battle in chronological order
    std::vector<ReplayAction*> actionList;
};

struct Report
{
    // Battle result
    // Who won, what loses on both sides
    // + a link to detailed list of events happened
    BattleSide winner;

    std::unique_ptr<Replay> replay;
};

class BattleProcessor
{
    // This class is doing battle between 2 armies providing replay with step by step information
    // about any portion of damage/control made
public:
    virtual std::unique_ptr<Report> Process(Army* armyA, Army* armyB) = 0;
};

