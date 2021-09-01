#include "battle.h"

#include "config.h"
#include "skills.h"

Battle::Battle()
    : mReport()
    , mRuntimeMarches()
    , mBattleFrameNum(0)
    , mMarches()
{
}

Battle::Battle(March* marchA, March* marchB)    
{
    AddParticipant(AttackSide::asAtk, marchA);
    AddParticipant(AttackSide::asDef, marchB);
}

void Battle::AddParticipant(AttackSide side, March* march)
{
    mRuntimeMarches[side].Init(side, march);
}

void Battle::Execute()
{
    Log::Print("\nBattle Start!");
    PreBattle();

    while (true)
    {
        const int numTroopsA = mRuntimeMarches[AttackSide::asAtk].CalcUnitedTroopsNum();
        const int numTroopsD = mRuntimeMarches[AttackSide::asDef].CalcUnitedTroopsNum();
        
        if (numTroopsA <= 0 || numTroopsD <= 0)
        {
            break;
        }

        FindTargets();
        MoveTroops();
        MakeDamage();  
        EnergyRegen();

        mBattleFrameNum += 1;
        if (mBattleFrameNum >= gConfig.GetMatchFrames())
        {
            // Timeout Defender Victory
        }
    }

    PostBattle();
}

void Battle::PreBattle()
{
    // TODO Should we start from 0 or from this?
    mBattleFrameNum = gConfig.GetUnitsRunIntoBattleFrames();

    mRuntimeMarches[AttackSide::asAtk].SetEnemy(&mRuntimeMarches[1]);
    mRuntimeMarches[AttackSide::asDef].SetEnemy(&mRuntimeMarches[0]);

    const RuntimeUnit& AA = mRuntimeMarches[AttackSide::asAtk].mRuntimeUnits[RuntimeUnitPosition::bupA];
    const RuntimeUnit& AB = mRuntimeMarches[AttackSide::asAtk].mRuntimeUnits[RuntimeUnitPosition::bupB];
    const RuntimeUnit& AC = mRuntimeMarches[AttackSide::asAtk].mRuntimeUnits[RuntimeUnitPosition::bupC];
    const RuntimeUnit& AD = mRuntimeMarches[AttackSide::asAtk].mRuntimeUnits[RuntimeUnitPosition::bupD];
          
    const RuntimeUnit& DA = mRuntimeMarches[AttackSide::asDef].mRuntimeUnits[RuntimeUnitPosition::bupA];
    const RuntimeUnit& DB = mRuntimeMarches[AttackSide::asDef].mRuntimeUnits[RuntimeUnitPosition::bupB];
    const RuntimeUnit& DC = mRuntimeMarches[AttackSide::asDef].mRuntimeUnits[RuntimeUnitPosition::bupC];
    const RuntimeUnit& DD = mRuntimeMarches[AttackSide::asDef].mRuntimeUnits[RuntimeUnitPosition::bupD];

    Log::Print("\nH%d(%d)\tH%d(%d)\t- H%d(%d)\tH%d(%d)",
        (AC.mHero ? AC.mHero->mPersona : -1), AC.mNumTroops,
        (AA.mHero ? AA.mHero->mPersona : -1), AA.mNumTroops,
        (DA.mHero ? DA.mHero->mPersona : -1), DA.mNumTroops,
        (DC.mHero ? DC.mHero->mPersona : -1), DC.mNumTroops);

    Log::Print("\nH%d(%d)\tH%d(%d)\t- H%d(%d)\tH%d(%d)\n",
        (AD.mHero ? AD.mHero->mPersona : -1), AD.mNumTroops,
        (AB.mHero ? AB.mHero->mPersona : -1), AB.mNumTroops,
        (DB.mHero ? DB.mHero->mPersona : -1), DB.mNumTroops,
        (DD.mHero ? DD.mHero->mPersona : -1), DD.mNumTroops);

    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        RuntimeMarch& rtMarch = mRuntimeMarches[i];        
        for (int j = 0; j < RuntimeUnitPosition::bupNUM; ++j)
        {
            RuntimeUnit& actor = rtMarch.mRuntimeUnits[j];
            for (int k = 0; k < actor.mSkills.Len(); ++k)
            {
                actor.mSkills[k]->OnBattleStart();
            }
        }
    }
}

bool Battle::FindTargets()
{
    bool ret = false;

    // Detect closest enemy march for all marches without mTarget
    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        RuntimeMarch& rtMarch = mRuntimeMarches[i];
        RuntimeMarch& rtEnemy = mRuntimeMarches[(i + 1) % AttackSide::asNUM];
        for (int j = 0; j < RuntimeUnitPosition::bupNUM; ++j)
        {
            RuntimeUnit& actor = rtMarch.mRuntimeUnits[j];
            if (actor.mTarget != nullptr)
            {
                continue;
            }
            float minDistSq = 1e9;
            for (int k = 0; k < RuntimeUnitPosition::bupNUM; ++k)
            {
                RuntimeUnit& actorEnemy = rtEnemy.mRuntimeUnits[k];
                if (actorEnemy.mNumTroops == 0)
                {
                    continue;
                }

                float d = (actor.mPos - actorEnemy.mPos).LenSq();
                if (d < minDistSq)
                {
                    actor.mTarget = &actorEnemy;
                    actor.SetConditionFlag(RuntimeUnitCondition::rucMoving);
                    minDistSq = d;
                    ret = true;
                }
            }
        }
    }

    return ret;
}

bool Battle::MoveTroops()
{
    bool ret = false;

    const float DistPerTick = gConfig.GetUnitMovementPerFrame();
    const float CloseUpDistanceSq = gConfig.GetUnitPlacementStopAtDistSq();
    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        RuntimeMarch& rtMarch = mRuntimeMarches[i];
        for (int j = 0; j < RuntimeUnitPosition::bupNUM; ++j)
        {
            RuntimeUnit& actor = rtMarch.mRuntimeUnits[j];
            if (actor.IsAlive() == false || actor.HasConditionFlag(RuntimeUnitCondition::rucMoving) == false)
            {
                continue;
            }

            // this is not accurate movement simulation, but I prefer speed over little time fluctuation here
            ASRT(actor.mTarget != nullptr);
            Vec2 dir = actor.mTarget->mPos - actor.mPos;
            if (dir.LenSq() <= CloseUpDistanceSq)
            {
                // We arrived
                actor.ClearConditionFlag(RuntimeUnitCondition::rucMoving);
            }
            else
            {
                actor.mPos.x += (dir.x == 0 ? 0 : (dir.x > 0 ? 1.f : -1.f)) * DistPerTick;
                actor.mPos.y += (dir.y == 0 ? 0 : (dir.y > 0 ? 1.f : -1.f)) * DistPerTick;
                ret = true;
            }
        }
    }

    return ret;
}

void Battle::MakeDamage()
{
    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        RuntimeMarch& rtMarch = mRuntimeMarches[i];
        for (int j = 0; j < RuntimeUnitPosition::bupNUM; ++j)
        {
            RuntimeUnit& actor = rtMarch.mRuntimeUnits[j];
            if (actor.IsAlive() == false)
            {
                continue;
            }
            
            // Check ulti
            if (actor.mEnergy >= Config::FULL_ENERGY)
            {
                Log::Print("\n[%d] ULTI %s", mBattleFrameNum, (actor.mOwner->mSide == AttackSide::asAtk ? "A" : "D"));
                actor.mSkills[0]->ForceActivate();
                actor.mEnergy = 0;
            }

            // TBD
             
            // Check auto attack
            float autoAttackReadyDelta = gConfig.GetDefaultAttacksPerFrame();
            actor.mAutoAttackReady += autoAttackReadyDelta;
            if (actor.mAutoAttackReady >= 1.f)
            {
                actor.mAutoAttackReady -= 1.f;
                AutoAttack(actor);
            }

            // Check TOK spells
            // TBD
        }
    }
}

int Battle::AutoAttack(RuntimeUnit& actor)
{
    const TroopKind myTroopKind = actor.mHero->mTroopKind;
    const int a = (int)(actor.mHero->GetStat(HeroStatType::hstPhysAtk)
        * gConfig.GetTroopStat(
            myTroopKind, 
            actor.mOwner->mMarch->mLord->mTroopTier[myTroopKind], 
            TroopsStatType::tstAtk));

    RuntimeUnit& actorEnemy = *actor.mTarget;
    const int troopsKilled = actorEnemy.TakeAutoAttackDamage(actor.mNumTroops, a);
    Log::Print("\n[%d] AA %s-> %d(-%d)", mBattleFrameNum, (actor.mOwner->mSide == AttackSide::asAtk ? "A" : "D"), actorEnemy.mNumTroops, troopsKilled);

    if (actorEnemy.mNumTroops <= 0)
    {
        actor.mTarget = nullptr;
        actorEnemy.mNumTroops = 0;
    }

    return troopsKilled;
}

void Battle::EnergyRegen()
{
    // Energy regen formula here - regen num is energy per sec + 10 energy for every 1% HP loss    
    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        RuntimeMarch& rtMarch = mRuntimeMarches[i];
        for (int j = 0; j < RuntimeUnitPosition::bupNUM; ++j)
        {
            RuntimeUnit& actor = rtMarch.mRuntimeUnits[j];
            if (actor.IsAlive() == false || actor.HasConditionFlag(RuntimeUnitCondition::rucMoving) == false)
            {
                continue;
            }
            const float dEn = actor.mHero->GetStat(HeroStatType::hstERegen) / gConfig.GetFPS();
            actor.mEnergy += dEn;
            // TODO - check if this truncates, or carries on
        }
    }
}

void Battle::PostBattle()
{
    const int numTroops[AttackSide::asNUM] = {
        mRuntimeMarches[AttackSide::asAtk].CalcUnitedTroopsNum()
      , mRuntimeMarches[AttackSide::asDef].CalcUnitedTroopsNum()
    };

    mReport.mResult = (numTroops[AttackSide::asDef] <= 0 ? BattleResult::brVictory : BattleResult::brDefeat);
    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        mReport.mLosses[i].numSurvived = numTroops[i];
        // TODO - how troops distributed between wounded/dead?
        mReport.mLosses[i].woundedLight = 0;
        mReport.mLosses[i].woundedHeavy = 0;
        mReport.mLosses[i].numDead = mRuntimeMarches[i].mMarch->CalcUnitedTroopsNum() - numTroops[i];

        // TODO - how kills converted to honor?
        mReport.mHonor[i] = 1;
    }
}

