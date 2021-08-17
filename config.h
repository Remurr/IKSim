#pragma once

#include "types.h"

class Config
{
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
    int   GetBattle—onvergenceFrames() { return 5 * GetFPS(); }
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