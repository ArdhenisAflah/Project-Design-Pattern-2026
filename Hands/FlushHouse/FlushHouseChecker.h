#pragma once
#include "../../PokerHandChecker.h"

class FlushHouseChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override;
    bool isFLushHouse(const Hand &hand);
};