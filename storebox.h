#pragma once
#include "types.h"

// TODO bad name
class Storebox
{
public:
    static Storebox& Inst();

    Lord*   NewLord() { mLords.push_back(Lord()); return &mLords.back(); }
    Dragon* NewDragon() { mDragons.push_back(Dragon()); return &mDragons.back(); }
    Hero*   NewHero() { mHeroes.push_back(Hero()); return &mHeroes.back(); }
    March*  NewMarch() { mMarches.push_back(March()); return &mMarches.back(); }

    std::vector<Lord>   mLords;
    std::vector<Dragon> mDragons;
    std::vector<Hero>   mHeroes;

    std::vector<March> mMarches;
};