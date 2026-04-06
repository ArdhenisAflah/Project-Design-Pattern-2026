#include <iostream>
#include "PairChecker.h"

HandRank PairChecker::check(const Hand &hand)
{
    if (isPair(hand))
    {
        std::cout << "Detected PAIR\n";
        return HandRank::PAIR;
    }
    return HandRank::HIGH_CARD;
}

bool PairChecker::isPair(const Hand &hand)
{
    return hand.value == 2;
}