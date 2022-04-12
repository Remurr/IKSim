#pragma once
#include "analytics.h"

class IKAnalytics : public Analytics, public Singleton<IKAnalytics>
{
public:
    void ShowShortReport(Report* report) override;
};
