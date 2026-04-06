#include <iostream>
#include "RoyalFlushChecker.h"

bool RoyalFlushChecker::check(const Hand &hand)
{
    if (isRoyalFlush(hand))
    {
        std::cout << "Detected ROYAL FLUSH\n";
        return true;
    }
    return false;
}

bool RoyalFlushChecker::isRoyalFlush(const Hand &hand)
{
    return hand.value == 10;
}