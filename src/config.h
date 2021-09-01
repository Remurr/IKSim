#pragma once
#include "enums.h"

struct StatModifier
{
    HeroStatType mType;
    float    mVal;
    bool     mIsPercent;
};

// TODO - do we need this?
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