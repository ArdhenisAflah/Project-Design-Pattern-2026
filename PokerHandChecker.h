#pragma once
#include "Hand.h"

class PokerHandChecker
{
public:
    virtual bool check(const Hand &hand) = 0;
};