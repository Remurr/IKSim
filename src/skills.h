#pragma once
#include "config.h"
#include "buffs.h"
#include "runtime_types.h"

struct RuntimeUnit;
class ISkill
{
public:    
    void Init(RuntimeUnit* owner, int lvl) { mOwner = owner; mLvl = lvl; InitInternal(); }

    virtual void ForceActivate() {}
    virtual void OnBattleStart() {}
    virtual void OnTimerTick() {}
    virtual void OnNormalAttackIn() {}
    virtual void OnNormalAttackOut() {}
    virtual void OnDamageIn() {}
    virtual void OnDamageOut() {}

    int GetLvl() { return mLvl; }

protected:
    virtual void InitInternal() = 0;

protected:
    RuntimeUnit* mOwner;
    int mLvl;
    float mValue;    
};

// Increases the Energy Regen Speed of 3 random units by N% for the first 12s of battle
// 15 20 25 30 35 40 45 50
class SkillRageBlessing : public ISkill
{    
public:
    void OnBattleStart() override 
    {
        RuntimeMarch* myMarch = mOwner->mOwner;
        myMarch->mRuntimeUnits[0].mBuffs.Add<BuffEnergyRegen>()->Init(mValue, (float)sDuration);
    }

protected:
    void InitInternal() override
    {
        // TODO Get values from config
        mValue = 25;
    }

    static const int sNumUnits = 3;
    static const int sDuration = 12;    
};

class HeroUlti_PierreTerrail : public ISkill
{
public:
    void ForceActivate() override
    {
        int skillVal = 0;
        gConfig.GetHeroUltiValue(mOwner->mHero->mPersona, mOwner->mHero->mSkillLvls[0], &skillVal);
        // TODO - what is the formula?
        mOwner->mTarget->TakeSkillDamage(skillVal * 1000);
    }
};