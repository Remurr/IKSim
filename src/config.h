#pragma once
#include "enums.h"

struct StatModifier
{
    StatType mType;
    float    mVal;
    bool     mIsPercent;
};

struct StatHolder
{
    void ApplyModifier(StatModifier modi) {}
    void RemoveModifier(StatModifier modi) {}
    float Get(StatType stat) const { return mValWithModifiers[stat]; }

    float mValOriginal[StatType::stNUM];
    float mValWithModifiers[StatType::stNUM];
};

class Config
{
public:
    static const int NUM_HEROES_IN_MARCH = 4;
    static const int NUM_EQUIPMENT_PIECES = 4;
    static const int NUM_SKILLS_ON_HERO = 4;
    static const int NUM_SKILLS_ON_DRAGON = 3;
    static const int INITIAL_ENERGY = 100;

public:
    void Init()
    {
        // TBD
    }

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

    // TODO!
    float GetTroopStat(TroopKind kind, TroopTier tier, StatType stat) { return 20; /*mTroopStats[kind][tier].val[stat];*/ }

private:
    StatHolder mTroopStats[TroopKind::tkNUM][TroopTier::ttNUM];
};

extern Config gConfig;