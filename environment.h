#pragma once

#include "types.h"

class Environment
{
public:
    virtual void Init() = 0;
    virtual March* GetMarch(AttackSide side) = 0; // TODO refactor
};


class TestEnvironmentA : public Environment
{
public:
    void Init() override;
    March* GetMarch(AttackSide side) override { return mMarches[side]; }

protected:
    void CreateDummyLord();
    void CreateDummyHero();
    void CreateDummyMarch();

private:        
    March* mMarches[AttackSide::asNUM];
};