#include <iostream>
#include "FullHouseChecker.h"

HandRank FullHouseChecker::check(const Hand &hand)
{
    if (isFullHouse(hand))
    {
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FullHouseChecker::isFullHouse(const Hand &hand)
{
    return true;
}
