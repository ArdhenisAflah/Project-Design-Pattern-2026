#include <iostream>
#include "RoyalFlushChecker.h"

HandRank RoyalFlushChecker::check(const Hand &hand)
{
    if (isRoyalFlush(hand))
    {
        std::cout << "Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }
    return HandRank::HIGH_CARD;
}

bool RoyalFlushChecker::isRoyalFlush(const Hand &hand)
{
    return hand.value == 10;
}