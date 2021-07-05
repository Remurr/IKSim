#pragma once
#include <vector>

#include "enums.h"

class AcademyTech
{
    // TBD
};

class AllianceTech
{
    // TBD
};

class ConsumableBuffs
{
    // TBD
};

class VIPBuffs
{
    int mVIPLvl;
    // TBD
};

class LordTalents
{
    // TBD
};

struct StatBuff
{
    StatType mStat;
    float mModifier;
    bool mIsPercent;
};

struct StatHolder
{
    float mStatValues[StatType::stNUM];
};

struct Dragon
{
    void SetLvl(int lvl) { mLvl = lvl; /*TODO get stats from config*/ }
    int GetLvl() { return mLvl; }

    ElementType mElem;
    int mSkillLvl[NUM_SKILLS_ON_DRAGON];

protected:
    int mLvl;
    StatHolder mStats;
};

struct Lord
{
    Faction   mFaction;
    std::vector<VIPBuffs> mVIPBuffs;
    std::vector<ConsumableBuffs> mConsumableBuffs;

    AcademyTech  mAcademyTech;
    AllianceTech mAllianceTech;
    LordTalents  mTalents;
};

struct Artifact
{
    ImmortalType mType;
    int mLvl;
    std::vector<StatBuff> mStats;

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
    // Avatar
    ElementType mElement;
    int mLvl;
    int mStars;
    int mBoostPlus;
    EquipmentPiece mEquipment[NUM_EQUIPMENT_PIECES];
    TowerOfKnowledgeSkills mSkills[MAX_TOK_SKILLS_ON_HERO];

    // Troops
    TroopType mTroopType;
    int       mTroopTier;
    int       mTroopNum;

    // TODO - I don't like the possibility to have stats in desync with source
    // All getters?
    int RecalcStatsAndPower() { return 0; }
    int GetPower() { return 0; }

protected:
    StatHolder mStatsFinal;
    int mPower;
};

struct March
{
    March()
        : mLord(nullptr)
        , mDragon(nullptr)
    {}

    Lord* mLord;
    Dragon* mDragon;
    std::vector<Hero*> mHeroes;

    // + active talent from LordTalents
};

struct Report
{
    struct TroopLoses
    {
        int numSurvived;
        int numDead;
        int woundedLight;
        int woundedHeavy;
    };

    BattleResult mResult;
    TroopLoses mLosses[AttackSide::asNUM];
    int mHonor[AttackSide::asNUM];

    // Defender only
    int mTrainingGroundDeath;
    int mProsperityLoss;
};