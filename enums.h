#pragma once

const int NUM_HEROES_IN_MARCH = 4;
const int NUM_EQUIPMENT_PIECES = 4;
const int MAX_TOK_SKILLS_ON_HERO = 3;
const int NUM_SKILLS_ON_DRAGON = 3;

enum AttackSide
{
    asAtk,
    asDef,
    
    asNUM,
};

enum BattleResult
{
    brVictory,
    brDefeat
};

enum TroopType
{
    ttCav,
    ttShield,
    ttSpear,
    ttBow,
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

    nlNUM,
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
    rGrey,
    rGreyPlus,
    rGreen,
    rGreenPlus,
    rBlue,
    rBluePlus,
    rPurple,
    rPurplePlus,
    rGold,
    rGoldPlus
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

    stNUM,
};

enum Faction
{
    fRED,
    fGREEN,
    fBLUE,
};

enum TowerOfKnowledgeSkills
{
    tokEmpty,
    tokOnslaught,
    tokWisdom,
    // TODO
    tokNUM,
};