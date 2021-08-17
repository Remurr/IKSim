#include "environment.h"
#include "storebox.h"

void TestEnvironmentA::Init()
{
    CreateDummyLord();
    CreateDummyHero();
    CreateDummyMarch();
}

void TestEnvironmentA::CreateDummyLord()
{
    Lord *lord = Storebox::Inst().NewLord();
    lord->mFaction = Faction::faBLUE;
    for (int i = 0; i < TroopKind::tkNUM; ++i)
    {
        lord->mTroopTier[i] = TroopTier::tt1;
    }
}

void TestEnvironmentA::CreateDummyHero()
{
    // Take Pierre Terrail
    Hero* hero = Storebox::Inst().NewHero();

    hero->mElement = ElementType::etWater;
    hero->mLvl = 1;
    hero->mStars = 0;
    hero->mBoostPlus = 0;
    for (int i = 0; i < NUM_EQUIPMENT_PIECES; ++i)
    {
        hero->mEquipment[i].mSlot = i;
        hero->mEquipment[i].mLvl = -1;
    }
    for (int i = 0; i < MAX_TOK_SKILLS_ON_HERO; ++i)
    {
        hero->mSkills[i] = TowerOfKnowledgeSkills::tokEmpty;
    }

    hero->mTroopKind = TroopKind::tkCav;
    hero->mTroopCouldLead = 4650;
}

void TestEnvironmentA::CreateDummyMarch()
{
    // Create 2 same test Marches for the beginning
    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        March* march = Storebox::Inst().NewMarch();
        march->mLord = &Storebox::Inst().mLords.back();
        march->mHeroes[BattleUnitPosition::bupA] = &Storebox::Inst().mHeroes.back();  
        march->mNumTroops[BattleUnitPosition::bupA] = 100;
    }
}