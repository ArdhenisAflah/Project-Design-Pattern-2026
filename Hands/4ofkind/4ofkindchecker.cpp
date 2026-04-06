#include <iostream>
#include "FourOfAKindChecker.h"

HandRank FourOfAKindChecker::check(const Hand &hand)
{
    if (isFourOfAKind(hand))
    {
        std::cout << "Detected FOUR OF A KIND\n";
        return true;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return false;
}

bool FourOfAKindChecker::isFourOfAKind(const Hand &hand)
{
    return true;
}