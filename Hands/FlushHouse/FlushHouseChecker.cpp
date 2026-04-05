#include <iostream>
#include "FlushHouseChecker.h"

bool FlushHouseChecker::check(const Hand &hand)
{
    if (isFLushHouse(hand))
    {
        std::cout << "Detected FLUSH HOUSE\n";
        return true;
    }
    return false;
}

bool FlushHouseChecker::isFLushHouse(const Hand &hand)
{
    return true;
}