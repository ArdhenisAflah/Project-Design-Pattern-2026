#include <iostream>
#include "PairChecker.h"

bool PairChecker::check(const Hand &hand)
{
    if (isPair(hand))
    {
        std::cout << "Detected PAIR\n";
        return true;
    }
    return false;
}

bool PairChecker::isPair(const Hand &hand)
{
    return true;
}