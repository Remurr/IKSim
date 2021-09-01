#pragma once

enum AttackSide
{
    asAtk,
    asDef,
    
    asNUM
};

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
    rucMoving           = 1 << 0,
    rucStun             = 1 << 1,
    rucNoAutoAttack     = 1 << 2, 
    rucNoSkills         = 1 << 3,
};

enum BattleResult
{
    brVictory,
    brDefeat,

    brNUM
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