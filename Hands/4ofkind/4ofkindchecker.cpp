#include <iostream>
#include "FourOfAKindChecker.h"

bool FourOfAKindChecker::check(const Hand &hand)
{
    if (isFourOfAKind(hand))
    {
        std::cout << "Detected FOUR OF A KIND\n";
        return true;
    }
    return false;
}

bool FourOfAKindChecker::isFourOfAKind(const Hand &hand)
{
    return true;
}