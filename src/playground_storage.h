#pragma once
#include "playground_types.h"

class PlaygroundStorageImpl;
class PlaygroundStorage
{
public:
    static PlaygroundStorage& Inst();

public:
    void Init();

    Lord*   NewLord(); 
    Dragon* NewDragon();
    Hero*   NewHero(); 
    March*  NewMarch();

    // I don't want to include <vector> to other files, but I don't like this proxy design..
    // TODO - think about it
    Lord*   LastLord(); 
    Dragon* LastDragon();
    Hero*   LastHero(); 
    March*  LastMarch();

protected:
    PlaygroundStorageImpl* mImpl;
};