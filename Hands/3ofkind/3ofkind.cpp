#include <iostream>
#include "3ofkind.h"

bool ThreeOfAKindChecker::check(const Hand &hand)
{
    if (isThreeOfAKind(hand))
    {
        std::cout << "Detected THREE OF A KIND\n";
        return true;
    }
    return false;
}

bool ThreeOfAKindChecker::isThreeOfAKind(const Hand &hand)
{
    return true;
}