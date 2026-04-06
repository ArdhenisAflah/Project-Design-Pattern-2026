#include <iostream>
#include "5ofkindchecker.h"

HandRank FiveOfAKindChecker::check(const Hand &hand)
{
    if (isFiveOfAKind(hand))
    {
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FiveOfAKindChecker::isFiveOfAKind(const Hand &hand)
{
    return hand.value == 11;
}
