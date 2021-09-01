#pragma once
#include "config.h"

class AcademyTech
{
    // TBD
};

class AllianceTech
{
    // TBD
};

class LordTalents
{
    // TBD
};



struct Dragon
{
    void SetLvl(int lvl) { mLvl = lvl; /*TODO get stats from config*/ }
    int GetLvl() { return mLvl; }

    ElementType mElem;
    int mSkillLvl[Config::NUM_SKILLS_ON_DRAGON];

protected:
    int mLvl;
    HeroStatHolder mStats;
};

struct Lord
{
    Faction   mFaction;
    //std::vector<VIPBuffs> mVIPBuffs;
    //std::vector<ConsumableBuffs> mConsumableBuffs;

    TroopTier    mTroopTier[TroopKind::tkNUM];
    AcademyTech  mAcademyTech;
    AllianceTech mAllianceTech;
    LordTalents  mTalents;
};

struct Artifact
{
    ImmortalType mType;
    int mLvl;
    //std::vector<StatBuff> mStats;

    int mStars;
    int specificSkillId; // TODO would it be convenient to have it this way? not sure
};

struct EquipmentPiece
{
    Rarity mRarity;
    ImmortalType mImmortalType;
    int mSlot; // 0-3
    int mLvl; // -1 means equipment non exist = empty slot
    ElementType mElement;
};

struct Hero
{
    Hero()
        : mPersona(hpNUM)
        , mElement(etNUM)
        , mLvl(0)
        , mStars(0)
        , mRuneLvl(0)
        , mEquipment()
        , mSkills()
        , mSkillLvls()
        , mTroopKind(tkNUM)
        , mTroopCouldLead(0)
        , mStats()
    {}

    // Avatar
    HeroPersona mPersona;
    ElementType mElement;
    int mLvl;
    int mStars;
    int mRuneLvl;
    EquipmentPiece mEquipment[Config::NUM_EQUIPMENT_PIECES];
    SkillRoster    mSkills[Config::NUM_SKILLS_ON_HERO];
    int            mSkillLvls[Config::NUM_SKILLS_ON_HERO];

    // Troops
    TroopKind mTroopKind;
    int       mTroopCouldLead;

    // TODO! Implement
    int GetPower() const { return 1; }
    float GetStat(HeroStatType stat) const 
    { 
        // TODO
        if (stat == HeroStatType::hstPhysAtk)
        {
            return 51.5f;
        }
        else if (stat == HeroStatType::hstPhysDef)
        {
            return 38.6f;
        }
        return 100;/*mStats.Get(stat);*/ 
    }

protected:
    HeroStatHolder mStats;
};

struct March
{
    March()
        : mLord(nullptr)
        , mDragon(nullptr)
        , mHeroes()
        , mNumTroops()
    {
    }

    int CalcUnitedTroopsNum() const;

    const Lord*   mLord;
    const Dragon* mDragon;
    const Hero*   mHeroes[RuntimeUnitPosition::bupNUM];
    int           mNumTroops[RuntimeUnitPosition::bupNUM];
};