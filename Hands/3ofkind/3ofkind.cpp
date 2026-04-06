#include <iostream>
#include "3ofkind.h"

HandRank ThreeOfAKindChecker::check(const Hand &hand)
{
    if (isThreeOfAKind(hand))
    {
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }
    return HandRank::HIGH_CARD;
}

bool ThreeOfAKindChecker::isThreeOfAKind(const Hand &hand)
{
    return hand.value == 4;
}