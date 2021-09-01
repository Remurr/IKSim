#include "runtime_types.h"
#include "skills.h"

RuntimeUnitPosition RuntimeUnit::GetBattleUnitPosition() const { return RuntimeUnitPosition((this - mOwner->mRuntimeUnits) / sizeof(RuntimeUnitPosition)); }

void RuntimeUnit::Init(RuntimeUnitPosition pos, RuntimeMarch* rtMarch)
{
    mTarget = nullptr;
    mOwner = rtMarch;
    mHero = rtMarch->mMarch->mHeroes[pos];
    if (mHero == nullptr)
    {
        return;
    }

    mNumTroops = rtMarch->mMarch->mNumTroops[pos];
    mEnergy = Config::INITIAL_ENERGY;
    mAutoAttackReady = 1.f;
    mConditionFlags = 0;

    // TODO positioning is pretty unclear for now
    // I would use mirroring for opposite side
    // C - A >> | >> A - C
    // D - B >> | >> B - D
    const float BetweenTroopsX = gConfig.GetUnitPlacementBetweenTroopsX();
    const float TroopToBorderX = gConfig.GetUnitPlacementTroopToBorderX();
    const float BetweenTroopsY = gConfig.GetUnitPlacementBetweenTroopsY();;
    const AttackSide side = rtMarch->mSide;
    if (pos == RuntimeUnitPosition::bupA) 
        mPos = Vec2((side == AttackSide::asDef ? 1.f : -1.f) * TroopToBorderX, 0);
    else if (pos == RuntimeUnitPosition::bupB) 
        mPos = Vec2((side == AttackSide::asDef ? 1.f : -1.f) * TroopToBorderX, BetweenTroopsY);
    else if (pos == RuntimeUnitPosition::bupC) 
        mPos = Vec2((side == AttackSide::asDef ? 1.f : -1.f) * (TroopToBorderX + BetweenTroopsX), 0);
    else if (pos == RuntimeUnitPosition::bupD) 
        mPos = Vec2((side == AttackSide::asDef ? 1.f : -1.f) * (TroopToBorderX + BetweenTroopsX), BetweenTroopsY);

    for (int i = 0; i < Config::NUM_SKILLS_ON_HERO; ++i)
    {
        if (mHero->mSkills[i] != SkillRoster::srEmpty)
        {
            ASRT(mHero->mSkillLvls[i] > 0);
            switch (mHero->mSkills[i])
            {
            case SkillRoster::srRageBlessing:
                mSkills.Add<SkillRageBlessing>()->Init(this, mHero->mSkillLvls[i]);
                break;
            default:
                break;
            }
        }
    }    
}

int RuntimeUnit::TakeAutoAttackDamage(int atackerNumTroops, int atackerTroopAtkStat)
{
    const TroopKind enemyTroopKind = mHero->mTroopKind;
    const float d = mHero->GetStat(HeroStatType::hstPhysDef)
        * gConfig.GetTroopStat(
            enemyTroopKind,
            mOwner->mMarch->mLord->mTroopTier[enemyTroopKind],
            TroopsStatType::tstDef);

    const int hp = gConfig.GetTroopStat(
        enemyTroopKind,
        mOwner->mMarch->mLord->mTroopTier[enemyTroopKind],
        TroopsStatType::tstHP);

    // NUM * 20 * (ah * at + 150) / (ah * at + 2 * dh * dt + 300) / hp
    const float Z = 20;
    const float K = 150;
    const float L = 300;
    float damageDone = atackerNumTroops * Z * (atackerTroopAtkStat + K) / (atackerTroopAtkStat + 2 * d + L) / hp;
    int troopsKilled = int(damageDone + 0.5f);

    mNumTroops -= troopsKilled;

    if (mNumTroops <= 0)
    {
        mNumTroops = 0;
    }

    return troopsKilled;
}

void RuntimeUnit::TakeSkillDamage(int amount)
{
    // TODO Dummy approach
    const TroopKind myTroopKind = mHero->mTroopKind;
    const int oneUnitHp = gConfig.GetTroopStat(myTroopKind,
        mOwner->mMarch->mLord->mTroopTier[myTroopKind],
        TroopsStatType::tstHP);
    mNumTroops -= amount / oneUnitHp;
}

void RuntimeMarch::Init(AttackSide side, March* staticMarch)
{
    if (staticMarch == nullptr)
        return;

    mMarch = staticMarch;
    mSide = side;
    for (int i = 0; i < RuntimeUnitPosition::bupNUM; ++i)
    {
        mRuntimeUnits[i].Init((RuntimeUnitPosition)i, this);
    }    
}

int RuntimeMarch::CalcUnitedTroopsNum() const
{
    int totalTroops = 0;
    for (int i = 0; i < RuntimeUnitPosition::bupNUM; ++i)
    {
        totalTroops += mRuntimeUnits[i].mNumTroops;
    }

    return totalTroops;
}

