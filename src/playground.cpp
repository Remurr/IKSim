#include "playground.h"
#include "playground_storage.h"

void TestPlaygroundA::Init()
{
    PlaygroundStorage::Inst().Init();
    CreateDummyLord();
    CreateDummyHero();
    CreateDummyMarch();
}

void TestPlaygroundA::CreateDummyLord()
{
    Lord *lord = PlaygroundStorage::Inst().NewLord();
    lord->mFaction = Faction::faBLUE;
    for (int i = 0; i < TroopKind::tkNUM; ++i)
    {
        lord->mTroopTier[i] = TroopTier::tt1;
    }
}

void TestPlaygroundA::CreateDummyHero()
{
    // Take Pierre Terrail
    Hero* hero = PlaygroundStorage::Inst().NewHero();

    hero->mPersona = HeroPersona::hpTEST;
    hero->mElement = ElementType::etWater;
    hero->mLvl = 1;
    hero->mStars = 0;
    hero->mRuneLvl = 0;
    for (int i = 0; i < Config::NUM_EQUIPMENT_PIECES; ++i)
    {
        hero->mEquipment[i].mSlot = i;
        hero->mEquipment[i].mLvl = -1;
    }
    hero->mSkills[0] = SkillRoster::srHeroUlti;
    hero->mSkillLvls[0] = 1;
    hero->mSkills[1] = SkillRoster::srRageBlessing;
    hero->mSkillLvls[1] = 2;

    hero->mTroopKind = TroopKind::tkCav;
    hero->mTroopCouldLead = 4650;
}

void TestPlaygroundA::CreateDummyMarch()
{
    // Create 2 same test Marches for the beginning
    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        March* march = PlaygroundStorage::Inst().NewMarch();

        mMarches[i] = march;
        march->mLord = PlaygroundStorage::Inst().LastLord();
        march->mHeroes[RuntimeUnitPosition::bupA] = PlaygroundStorage::Inst().LastHero();
        march->mNumTroops[RuntimeUnitPosition::bupA] = 1000;
    }
}