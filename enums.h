#pragma once

const int NUM_HEROES_IN_MARCH = 4;
const int NUM_EQUIPMENT_PIECES = 4;
const int MAX_TOK_SKILLS_ON_HERO = 3;
const int NUM_SKILLS_ON_DRAGON = 3;

enum AttackSide
{
    asAtk,
    asDef,
    
    asNUM
};

// C(range) - A(melee)
// D(range) - B(melee)
enum BattleUnitPosition
{
    bupA,
    bupB,
    bupC,
    bupD,

    bupNUM
};

enum BattleUnitCondition
{
    bucMoving           = 1 << 0,
    bucStun             = 1 << 1,
    bucNoAutoAttack     = 1 << 2, 
    bucNoSkills         = 1 << 3,
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
enum HeroName
{
    //Water
    hnMerlin,
    //Fire
    //Wind
    //Lightning
    //Earth
    hnAlexander,
    hnCharles,
    hnZenobia,
    hnCleo,
    hnLeonid,
    //Shadow
    //Holy
    hnNUM
};

enum StatType
{
    stPhysAtk,
    stPhysDef,
    stMagicAtk,
    stMagicDef,
    stCrit,
    stDodge,
    stAccuracy,
    stResil,
    stERegen,
    stHP,

    stNUM
};

enum Faction
{
    faRED,
    faGREEN,
    faBLUE,

    faNUM
};

enum TowerOfKnowledgeSkills
{
    tokEmpty,
    tokOnslaught,
    tokWisdom,
    // TODO

    tokNUM
};