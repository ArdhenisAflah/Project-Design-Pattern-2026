#include <iostream>
#include "4ofkindchecker.h"

HandRank FourOfAKindChecker::check(const Hand &hand)
{
    if (isFourOfAKind(hand))
    {
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FourOfAKindChecker::isFourOfAKind(const Hand &hand)
{
    return true;
}