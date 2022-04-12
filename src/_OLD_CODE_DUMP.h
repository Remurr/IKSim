#pragma once

/*
class Battle
{
public:
    Battle();
    Battle(March* marchA, March* marchB);

    void AddParticipant(AttackSide pt, March* march);

    void Execute();

    const Report* GetReport() const { return &mReport; }

private:
    void PreBattle();
    void PostBattle();

    bool FindTargets();
    bool MoveTroops();
    void MakeDamage();
    void EnergyRegen();

    int  AutoAttack(RuntimeUnit& actor);

private:
    Report       mReport;
    RuntimeMarch mRuntimeMarches[AttackSide::asNUM];
    int          mBattleFrameNum;

    March* mMarches[AttackSide::asNUM];
};

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

struct Dragon
{
    void SetLvl(int lvl) { mLvl = lvl;  } //TODO get stats from config
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
        return 100;//mStats.Get(stat);
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

    const Lord* mLord;
    const Dragon* mDragon;
    const Hero* mHeroes[RuntimeUnitPosition::bupNUM];
    int           mNumTroops[RuntimeUnitPosition::bupNUM];
};

class TestPlaygroundA : public Playground
{
public:
    void Init() override;
    March* GetMarch(AttackSide side) override { return mMarches[side]; }

protected:
    void CreateDummyLord();
    void CreateDummyHero();
    void CreateDummyMarch();

private:
    March* mMarches[AttackSide::asNUM];
};

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

*/