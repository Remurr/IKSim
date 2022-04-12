#pragma once

/*
// C(range) - A(melee)
// D(range) - B(melee)
enum RuntimeUnitPosition
{
    bupA,
    bupB,
    bupC,
    bupD,

    bupNUM
};

enum RuntimeUnitCondition
{
    rucMoving = 1 << 0,
    rucStun = 1 << 1,
    rucNoAutoAttack = 1 << 2,
    rucNoSkills = 1 << 3,
};



enum TroopKind
{
    tkCav,
    tkShield,
    tkSpear,
    tkBow,

    tkNUM
};

enum TroopTier
{
    tt1,
    tt2,
    tt3,
    tt4,
    tt5,

    ttNUM
};

enum SkillTier
{
    sktNone = 0,
    skt0 = sktNone,
    skt1,
    skt2,
    skt3,
    skt4,
    skt5,
    skt6,
    skt7,
    skt8,
    sktMAX = skt8,

    sktNUM
};

enum NobilityLevel
{
    nlKnight3,
    nlKnight2,
    nlKnight1,
    nlBaron3,
    nlBaron2,
    nlBaron1,
    nlViscount3,
    nlViscount2,
    nlViscount1,
    nlCount4,
    nlCount3,
    nlCount2,
    nlCount1,
    nlMarquis4,
    nlMarquis3,
    nlMarquis2,
    nlMarquis1,
    nlDuke,
    nlArchduke,
    nlPrince,

    nlNUM
};

enum ImmortalType
{
    itDefense,
    itAttack,
    itRange,
    itMagic,
    itSupport,

    itNUM
};

enum Rarity
{
    rrGrey,
    rrGreyPlus,
    rrGreen,
    rrGreenPlus,
    rrBlue,
    rrBluePlus,
    rrPurple,
    rrPurplePlus,
    rrGold,
    rrGoldPlus,

    rNUM
};

enum ElementType
{
    etWater,
    etFire,
    etWind,
    etLightning,
    etEarth,
    etShadow,
    etHoly,

    etNUM
};

// TODO
enum HeroPersona
{
    //Water
    hpMerlin,
    //Fire
    //Wind
    //Lightning
    //Earth
    hpAlexander,
    hpCharles,
    hpZenobia,
    hpCleo,
    hpLeonid,
    //Shadow
    //Holy
    hpTEST,
    hpNUM
};

enum TroopsStatType
{
    tstAtk,
    tstDef,
    tstHP,

    tstNUM
};

enum HeroStatType
{
    hstPhysAtk,
    hstPhysDef,
    hstMagicAtk,
    hstMagicDef,
    hstCrit,
    hstDodge,
    hstAccuracy,
    hstResil,
    hstERegen,
    hstHP,

    hstNUM
};

enum Faction
{
    faRED,
    faGREEN,
    faBLUE,

    faNUM
};

enum SkillRoster
{
    srEmpty,
    srHeroUlti,

    // TEST ONE
    srRageBlessing,

    // TOK
    srOnslaught,
    srWisdom,
    // TODO
    //...

    srNUM
};

enum BuffType
{
    btStats,
    btControlImmune,

    btNUM
};

struct StatModifier
{
    HeroStatType mType;
    float    mVal;
    bool     mIsPercent;
};

//? TODO - do we need this?
struct HeroStatHolder
{
    void ApplyModifier(StatModifier modi) {}
    void RemoveModifier(StatModifier modi) {}
    float Get(HeroStatType stat) const { return mValWithModifiers[stat]; }

    float mValOriginal[HeroStatType::hstNUM];
    float mValWithModifiers[HeroStatType::hstNUM];
};

class ConfigImpl;
class Config
{
public:
    static const int NUM_HEROES_IN_MARCH = 4;
    static const int NUM_EQUIPMENT_PIECES = 4;
    static const int NUM_SKILLS_ON_HERO = 4;
    static const int NUM_SKILLS_ON_DRAGON = 3;
    static const int INITIAL_ENERGY = 100;
    static const int FULL_ENERGY = 1000;
    static const int MAX_SKILL_LVL = 8;

public:
    Config() : mImpl(nullptr) {}
    ~Config();
    void Init();

    int GetFPS() { return 10; }
    int GetMatchFrames() { return 90 * GetFPS(); }

    // Hero
    float GetDefaultAttacksPerFrame() { return 1.f / GetFPS(); }

    // Unit movement
    int   GetUnitsRunIntoBattleFrames() { return 5 * GetFPS(); }
    float GetUnitMovementPerFrame() { return 0.5f / GetFPS(); }
    float GetUnitPlacementBetweenTroopsX() { return 2.f; }
    float GetUnitPlacementTroopToBorderX() { return 1.f; }
    float GetUnitPlacementBetweenTroopsY() { return 1.f; }
    float GetUnitPlacementStopAtDistSq() { return 0.5f * 0.5f; }

    int  GetTroopStat(TroopKind kind, TroopTier tier, TroopsStatType stat);
    void GetHeroUltiValue(HeroPersona persona, int lvl, int* outA, int* outB = nullptr, int* outC = nullptr);
    
private:
    ConfigImpl* mImpl;    
};

extern Config gConfig;
*/