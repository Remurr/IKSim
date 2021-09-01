#include "config.h"
#include "log.h"
#include <vector>

Config gConfig;

class ConfigImpl
{
public:
    int mTroopStats[TroopKind::tkNUM][TroopTier::ttNUM][TroopsStatType::tstNUM];
    std::vector<int> mHeroUltiValueA[HeroPersona::hpNUM];
    std::vector<int> mHeroUltiValueB[HeroPersona::hpNUM];
    std::vector<int> mHeroUltiValueC[HeroPersona::hpNUM];
};
Config::~Config()
{
    if (mImpl != nullptr)
    {
        delete mImpl;
    }

    mImpl = nullptr;
}

void Config::Init()
{
    mImpl = new ConfigImpl();
    
    // TODO
    mImpl->mHeroUltiValueA[HeroPersona::hpTEST] = { 165, 220, 275, 330, 385, 440, 495, 550 };

    mImpl->mTroopStats[TroopKind::tkCav][TroopTier::tt1][TroopsStatType::tstAtk] = 25;
    mImpl->mTroopStats[TroopKind::tkCav][TroopTier::tt1][TroopsStatType::tstDef] = 16;
    mImpl->mTroopStats[TroopKind::tkCav][TroopTier::tt1][TroopsStatType::tstHP] = 128;
}

int Config::GetTroopStat(TroopKind kind, TroopTier tier, TroopsStatType stat)
{ 
    return mImpl->mTroopStats[kind][tier][stat];
}

void Config::GetHeroUltiValue(HeroPersona persona, int lvl, int* outA, int* outB, int* outC)
{    
    ASRT(lvl > 0 && lvl <= MAX_SKILL_LVL);
    *outA = mImpl->mHeroUltiValueA[persona][lvl];

    if (outB != nullptr)
    {
        *outB = mImpl->mHeroUltiValueB[persona][lvl];
    }
    if (outC != nullptr)
    {
        *outC = mImpl->mHeroUltiValueC[persona][lvl];
    }
}


