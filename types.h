#pragma once
#include <vector>

#include "enums.h"
#include "log.h"

struct Vec2
{
    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) { }
    float LenSq() const { return x * x + y * y; }    

    Vec2 operator+(Vec2 p) { return p += *this; }
    Vec2 operator+=(const Vec2& p) { x += p.x; y += p.y; return *this; }
    Vec2 operator-(Vec2 p) { return p -= *this; }
    Vec2 operator-=(const Vec2& p) { x -= p.x; y -= p.y; return *this; }

    float x;
    float y;
};

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
    float val[StatType::stNUM];
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

    TroopTier    mTroopTier[TroopKind::tkNUM];
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
    TroopKind mTroopKind;    
    int       mTroopCouldLead;

    // TODO - I don't like the possibility to have stats in desync with source
    int RecalcStatsAndPower() { return 0; }
    
    // TODO! Implement
    int GetPower() const { return 1; }
    float GetStat(StatType stat) const { return 30;  /*mStatsFinal.val[stat];*/ }

protected:
    StatHolder mStatsFinal;
    int mPower;
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
    const Hero*   mHeroes[BattleUnitPosition::bupNUM];
    int           mNumTroops[BattleUnitPosition::bupNUM];    
};

struct RuntimeMarch;
struct BattleUnit
{
    BattleUnit()
        : mTarget(nullptr)
        , mParent(nullptr)
        , mHero(nullptr)
        , mNumTroops(0)
        , mEnergy(0)
        , mAutoAttackReady(0)
        , mPos(0, 0)
        , mFlags(0)
    {}

    void SetFlag(BattleUnitCondition flag) { mFlags |= flag; }
    void ClearFlag(BattleUnitCondition flag) { unsigned int tmp = flag; mFlags &= ~tmp; }
    void ClearAllFlags() { mFlags = 0; }
    bool HasFlag(BattleUnitCondition flag) const { return mFlags & flag; }
    bool IsAlive() const { return mHero != nullptr && mNumTroops > 0; }

    // TODO maybe cache?
    BattleUnitPosition GetBattleUnitPosition() const;

    BattleUnit*   mTarget;
    RuntimeMarch* mParent;
    const Hero*   mHero;

    int   mNumTroops;
    float mEnergy;
    float mAutoAttackReady;
    Vec2  mPos;
    unsigned int mFlags;
};

struct RuntimeMarch
{
    RuntimeMarch()
        : mMarch(nullptr)
        , mBattleUnits()
        , mSide(AttackSide::asNUM)
    {}

    void Init(AttackSide side, March* staticMarch);
    int CalcUnitedTroopsNum() const;

    const March* mMarch;
    BattleUnit   mBattleUnits[BattleUnitPosition::bupNUM];
    AttackSide   mSide;
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

    Report()
        : mResult(BattleResult::brNUM)
        , mLosses()
        , mHonor()
        , mTrainingGroundDeath(0)
        , mProsperityLoss(0)
    {}

    BattleResult mResult;
    TroopLoses   mLosses[AttackSide::asNUM];
    int          mHonor[AttackSide::asNUM];

    // Defender only
    int mTrainingGroundDeath;
    int mProsperityLoss;
};