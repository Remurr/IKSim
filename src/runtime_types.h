#pragma once
#include "common_types.h"
#include "playground_types.h"

class ISkill;
class IBuff;
struct RuntimeMarch;
struct RuntimeUnit
{
    RuntimeUnit()
        : mTarget(nullptr)
        , mOwner(nullptr)
        , mHero(nullptr)
        , mNumTroops(0)
        , mEnergy(0)
        , mAutoAttackReady(0)
        , mPos(0, 0)
        , mConditionFlags(0)
        , mSkills()
        , mBuffs()
    {}

    void Init(RuntimeUnitPosition pos, RuntimeMarch *rtMarch);

    bool IsAlive() const { return mHero != nullptr && mNumTroops > 0; }

    void SetConditionFlag(RuntimeUnitCondition flag) { mConditionFlags |= flag; }
    void ClearConditionFlag(RuntimeUnitCondition flag) { unsigned int tmp = flag; mConditionFlags &= ~tmp; }
    void ClearAllConditionFlags() { mConditionFlags = 0; }
    bool HasConditionFlag(RuntimeUnitCondition flag) const { return mConditionFlags & flag; }

    void TakeSkillDamage(int amount);
    int TakeAutoAttackDamage(int atackerNumTroops, int atackerTroopAtkStat);

    // TODO maybe cache?
    RuntimeUnitPosition GetBattleUnitPosition() const;

public:
    RuntimeUnit* mTarget;
    RuntimeMarch* mOwner;
    const Hero* mHero;

    int   mNumTroops;
    float mEnergy;
    float mAutoAttackReady;
    Vec2  mPos;
    unsigned int mConditionFlags;

    static const int MAX_BUFFS_ON_UNIT = 16;
    InplaceInterfaceHolder<ISkill*, 40, Config::NUM_SKILLS_ON_HERO> mSkills;
    InplaceInterfaceHolder<IBuff*, 40, MAX_BUFFS_ON_UNIT> mBuffs;
};

struct RuntimeMarch
{
    RuntimeMarch()
        : mMarch(nullptr)
        , mRuntimeUnits()
        , mSide(AttackSide::asNUM)
        , mEnemy(nullptr)
    {}

    void Init(AttackSide side, March* staticMarch);
    void SetEnemy(RuntimeMarch* enemy) { mEnemy = enemy; }
    int CalcUnitedTroopsNum() const;

public:
    const March* mMarch;
    RuntimeUnit  mRuntimeUnits[RuntimeUnitPosition::bupNUM];
    AttackSide   mSide;
    RuntimeMarch* mEnemy;
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
