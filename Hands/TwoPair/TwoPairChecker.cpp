#include <iostream>
#include "TwoPairChecker.h"

HandRank TwoPairChecker::check(const Hand &hand)
{
    if (isTwoPair(hand))
    {
        std::cout << "Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool TwoPairChecker::isTwoPair(const Hand &hand)
{
    return true;
}
