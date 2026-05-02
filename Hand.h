#pragma once
#include <vector>
#include "Card.h"

struct Hand
{
    int value;
    std::vector<Card> cards;
};