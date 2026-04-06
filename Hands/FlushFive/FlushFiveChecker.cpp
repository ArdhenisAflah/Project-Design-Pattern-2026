#include <iostream>
#include "FlushFiveChecker.h"

HandRank FlushFiveChecker::check(const Hand &hand)
{
    if (isFlushFiveChecker(hand))
    {
        std::cout << "Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FlushFiveChecker::isFlushFiveChecker(const Hand &hand)
{
    return hand.value == 13;
}
