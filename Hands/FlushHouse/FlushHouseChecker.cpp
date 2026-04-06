#include <iostream>
#include "FlushHouseChecker.h"

HandRank FlushHouseChecker::check(const Hand &hand)
{
    if (isFLushHouse(hand))
    {
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }

    if (nextChecker)
    {
        nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FlushHouseChecker::isFLushHouse(const Hand &hand)
{
    return hand.value == 12;
}