#include "battle.h"

#include "config.h"

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
    PreBattle();

    while (true)
    {
        const int numTroopsA = mRuntimeMarches[AttackSide::asAtk].GetNumTroops();
        const int numTroopsD = mRuntimeMarches[AttackSide::asDef].GetNumTroops();
        
        if (numTroopsA == 0 || numTroopsD == 0)
        {
            break;
        }

        FindTargets();
        MoveTroops();
        MakeDamage();  

        mFrames += 1;
        if (mFrames >= gConfig.GetMatchFrames())
        {
            // Timeout Defender Victory
        }
    }
}

void Battle::PreBattle()
{
    mFrames = gConfig.GetBattleŅonvergenceFrames();
}

bool Battle::FindTargets()
{
    bool ret = false;

    // Detect closest enemy march for all marches without mTarget
    for (int i = 0; i < AttackSide::asNUM; ++i)
    {
        RuntimeMarch& rtMarch = mRuntimeMarches[i];
        RuntimeMarch& rtEnemy = mRuntimeMarches[(i + 1) % AttackSide::asNUM];
        for (int j = 0; j < BattleUnitPosition::bupNUM; ++j)
        {
            BattleUnit& actor = rtMarch.mBattleUnits[j];
            if (actor.mTarget != nullptr)
            {
                continue;
            }
            float minDistSq = 1e9;
            for (int k = 0; k < BattleUnitPosition::bupNUM; ++k)
            {
                BattleUnit& actorEnemy = rtEnemy.mBattleUnits[k];
                if (actorEnemy.mNumTroops == 0)
                {
                    continue;
                }

                float d = (actor.mPos - actorEnemy.mPos).LenSq();
                if (d < minDistSq)
                {
                    actor.mTarget = &actorEnemy;
                    actor.SetFlag(BattleUnitCondition::bucMoving);
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
        for (int j = 0; j < BattleUnitPosition::bupNUM; ++j)
        {
            BattleUnit& actor = rtMarch.mBattleUnits[j];
            if (actor.IsAlive() == false || actor.HasFlag(BattleUnitCondition::bucMoving) == false)
            {
                continue;
            }

            // this is not accurate movement simulation, but I prefer speed over little time fluctuation here
            ASRT(actor.mTarget != nullptr);
            Vec2 dir = actor.mTarget->mPos - actor.mPos;
            if (dir.LenSq() <= CloseUpDistanceSq)
            {
                // We arrived
                actor.ClearFlag(BattleUnitCondition::bucMoving);
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
        for (int j = 0; j < BattleUnitPosition::bupNUM; ++j)
        {
            BattleUnit& actor = rtMarch.mBattleUnits[j];
            if (actor.IsAlive() == false)
            {
                continue;
            }
            
            // Check ulti
            // TBD
             
            // Check auto attack
            float autoAttackReadyDelta = gConfig.GetDefaultAttacksPerFrame();
            actor.mAutoAttackReady += autoAttackReadyDelta;
            if (actor.mAutoAttackReady >= 1.f)
            {
                actor.mAutoAttackReady -= 1.f;
                AutoAttack(actor);
            }

            // Check TOK stells
            // TBD
        }
    }
}

int Battle::AutoAttack(BattleUnit& actor)
{
    const TroopKind myTroopKind = actor.mHero->mTroopKind;
    const float a = actor.mHero->GetStat(StatType::stPhysAtk)
        * gConfig.GetTroopStat(
            myTroopKind, 
            actor.mParent->mMarch->mLord->mTroopTier[myTroopKind], 
            StatType::stPhysAtk);

    BattleUnit& actorEnemy = *actor.mTarget;
    const TroopKind enemyTroopKind = actorEnemy.mHero->mTroopKind;
    const float d = actorEnemy.mHero->GetStat(StatType::stPhysDef)
        * gConfig.GetTroopStat(
            enemyTroopKind, 
            actorEnemy.mParent->mMarch->mLord->mTroopTier[enemyTroopKind],
            StatType::stPhysDef);

    const float hp = gConfig.GetTroopStat(
        enemyTroopKind,
        actorEnemy.mParent->mMarch->mLord->mTroopTier[enemyTroopKind],
        StatType::stHP);

    // NUM * 20 * (ah * at + 150) / (ah * at + 2 * dh * dt + 300) / hp
    const float Z = 20;
    const float K = 150;
    const float L = 300;
    float damageDone = actor.mNumTroops * Z * (a + K) / (a + 2 * d + L) / hp;
    int troopsKilled = int(damageDone + 0.5f);

    Log::Print("\n%x -> %x (-%d)", &actor, &actorEnemy, troopsKilled);

    actorEnemy.mNumTroops -= troopsKilled;    
    if (actorEnemy.mNumTroops <= 0)
    {
        actor.mTarget = nullptr;
    }

    return troopsKilled;
}


