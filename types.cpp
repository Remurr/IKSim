#include "types.h"

#include "config.h"

BattleUnitPosition BattleUnit::GetBattleUnitPosition() const { return BattleUnitPosition((this - mParent->mBattleUnits) / sizeof(BattleUnitPosition)); }

void RuntimeMarch::Init(AttackSide side, March* staticMarch)
{
    if (staticMarch == nullptr)
        return;

    mMarch = staticMarch;
    mSide = side;
    for (int i = 0; i < BattleUnitPosition::bupNUM; ++i)
    {
        mBattleUnits[i].mParent = this;
        mBattleUnits[i].mHero = staticMarch->mHeroes[i];
        mBattleUnits[i].mNumTroops = staticMarch->mNumTroops[i];
        mBattleUnits[i].mEnergy = 0; // TODO count talents/skills initial energy
        mBattleUnits[i].mAutoAttackReady = 1.f;
    }
    // TODO positioning is pretty unclear for now
    // I would use mirroring for opposite side
    // C - A >> | >> A - C
    // D - B >> | >> B - D
    const float BetweenTroopsX = gConfig.GetUnitPlacementBetweenTroopsX();
    const float TroopToBorderX = gConfig.GetUnitPlacementTroopToBorderX();
    const float BetweenTroopsY = gConfig.GetUnitPlacementBetweenTroopsY();;
    mBattleUnits[BattleUnitPosition::bupA].mPos = Vec2((side == AttackSide::asDef ? 1.f : -1.f) * TroopToBorderX, 0);
    mBattleUnits[BattleUnitPosition::bupB].mPos = Vec2((side == AttackSide::asDef ? 1.f : -1.f) * TroopToBorderX, BetweenTroopsY);
    mBattleUnits[BattleUnitPosition::bupC].mPos = Vec2((side == AttackSide::asDef ? 1.f : -1.f) * (TroopToBorderX + BetweenTroopsX), 0);
    mBattleUnits[BattleUnitPosition::bupD].mPos = Vec2((side == AttackSide::asDef ? 1.f : -1.f) * (TroopToBorderX + BetweenTroopsX), BetweenTroopsY);
}

int RuntimeMarch::CalcUnitedTroopsNum() const
{
    int totalTroops = 0;
    for (int i = 0; i < BattleUnitPosition::bupNUM; ++i)
    {
        totalTroops += mBattleUnits[i].mNumTroops;
    }

    return totalTroops;
}

int March::CalcUnitedTroopsNum() const
{
    int totalTroops = 0;
    for (int i = 0; i < BattleUnitPosition::bupNUM; ++i)
    {
        totalTroops += mNumTroops[i];
    }

    return totalTroops;
}