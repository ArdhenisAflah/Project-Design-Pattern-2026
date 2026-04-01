#include <iostream>
#include "FlushChecker.h"

bool FlushChecker::check(const Hand &hand)
{
    if (isFlush(hand))
    {
        std::cout << "Detected FLUSH\n";
        return true;
    }
    return false;
}

bool FlushChecker::isFlush(const Hand &hand)
{
    return true;
}
