#pragma once
#include "../../PokerHandChecker.h"
class FlushChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override;
    bool isFlush(const Hand &hand);
};