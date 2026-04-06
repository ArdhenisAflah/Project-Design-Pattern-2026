#include <iostream>
#include "FlushChecker.h"

HandRank FlushChecker::check(const Hand &hand)
{
    if (isFlush(hand))
    {
        std::cout << "Detected FLUSH\n";
        return HandRank::FLUSH;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FlushChecker::isFlush(const Hand &hand)
{
    return hand.value == 6;
}
