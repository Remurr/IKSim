#pragma once
#include <memory>

#include "common.h"

struct March
{
    // Units and heroes that fight
};

struct Account
{
    // All static bonuses that appiles to a march
    // academy tech, alliance tech, VIP lvl, title buffs etc
};

struct TemporaryArmyBuffs
{
    // All temporary bonuses that appiles to a march
    // Consumable buffs, buffs/debuffs from standing on alliance territory etc
};

struct Army
{
    // Army is a combination of units that fight with application of account and temporary buffs
    std::unique_ptr<March> march;
    std::unique_ptr<Account> account;
    std::unique_ptr<TemporaryArmyBuffs> tmpBuffs;
};


class ArmyProvider
{
    // This class builds an army from user input
public:    
    virtual std::unique_ptr<Army> GetArmy(BattleSide side) = 0;
};