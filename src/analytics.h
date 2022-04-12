#pragma once
#include "common.h"
#include "battle_processor.h"

class Analytics
{
    // The purpose of this class is to give efficiency evaluation of various heroes, skills, technologies     
public:
    virtual void ShowShortReport(Report* report) = 0;
    // virtual void Analyze(Report* report) = 0;

    //? TBD - need much more of utility here
    // several reports average, report vs report analyze etc
};

