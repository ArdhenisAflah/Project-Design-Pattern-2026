#pragma once
#include "../../PokerHandChecker.h"

class FlushHouseChecker : public PokerHandChecker
{
public:
    bool check(const Hand &hand) override;
    bool isFLushHouse(const Hand &hand);
};