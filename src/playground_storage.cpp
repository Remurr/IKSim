#include "playground_storage.h"
#include <vector>

namespace
{
    PlaygroundStorage s_Inst;
}
PlaygroundStorage& PlaygroundStorage::Inst() { return s_Inst; }

class PlaygroundStorageImpl
{
public:
    std::vector<Lord*>   mLords;
    std::vector<Dragon*> mDragons;
    std::vector<Hero*>   mHeroes;
    std::vector<March*>  mMarches;
};

void PlaygroundStorage::Init()
{
    mImpl = new PlaygroundStorageImpl();
}

Lord* PlaygroundStorage::NewLord() 
{ 
    mImpl->mLords.push_back(new Lord());
    return mImpl->mLords.back();
}
Dragon* PlaygroundStorage::NewDragon() 
{ 
    mImpl->mDragons.push_back(new Dragon());
    return mImpl->mDragons.back();
}
Hero* PlaygroundStorage::NewHero() 
{ 
    mImpl->mHeroes.push_back(new Hero());
    return mImpl->mHeroes.back();
}
March* PlaygroundStorage::NewMarch() 
{ 
    mImpl->mMarches.push_back(new March());
    return mImpl->mMarches.back();
}
Lord*   PlaygroundStorage::LastLord(){ return mImpl->mLords.back(); } 
Dragon* PlaygroundStorage::LastDragon(){ return mImpl->mDragons.back(); }
Hero*   PlaygroundStorage::LastHero(){ return mImpl->mHeroes.back(); } 
March*  PlaygroundStorage::LastMarch(){ return mImpl->mMarches.back(); }

