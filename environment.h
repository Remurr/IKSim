#pragma once

#include "types.h"

class Environment
{
public:
    virtual void Init() = 0;
    virtual March* GetMarch(AttackSide side) = 0;
};


class TestEnvironmentA : public Environment
{
public:
    void Init() override
    {
        CreateDummyLord();
        CreateDummyHero();

        // Create 2 same test Marches for the beginning
        for (int i = 0; i < AttackSide::asNUM; ++i)
        {
            March& march = mMarches[i];
            march.mHeroes.push_back(&mTestHero);
            march.mLord = &mTestLord;
        }
    }

    March* GetMarch(AttackSide side) override
    {
        return &mMarches[side];
    }

protected:
    void CreateDummyLord()
    {
        mTestLord.mFaction = Faction::fBLUE;
    }

    void CreateDummyHero()
    {
        // Take Pierre Terrail
        mTestHero.mElement = ElementType::etWater;
        mTestHero.mLvl = 1;
        mTestHero.mStars = 0;
        mTestHero.mBoostPlus = 0;
        for (int i = 0; i < NUM_EQUIPMENT_PIECES; ++i)
        {
            mTestHero.mEquipment[i].mSlot = i;
            mTestHero.mEquipment[i].mLvl = -1;
        }
        for (int i = 0; i < MAX_TOK_SKILLS_ON_HERO; ++i)
        {
            mTestHero.mSkills[i] = TowerOfKnowledgeSkills::tokEmpty;
        }

        mTestHero.mTroopType = TroopType::ttCav;
        mTestHero.mTroopTier = 4;
        mTestHero.mTroopNum = 4650;
    }

private:    
    Lord  mTestLord;
    Hero  mTestHero;
    March mMarches[AttackSide::asNUM];
};