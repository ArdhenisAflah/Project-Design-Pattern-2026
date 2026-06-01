#pragma once
#include "Hand.h"
#include <algorithm>
class CardUtils
{
public:
    static void SortRank(Hand &hands);
    static void PrintCards(Hand cards);
};