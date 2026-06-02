#pragma once
#include "PokerHandChecker.h"

class IHandUpgrade
{
public:
    virtual ~IHandUpgrade() = default;
    virtual void upgrade(HandRank rank) = 0;
};