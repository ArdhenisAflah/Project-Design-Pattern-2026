#include <iostream>
#include "FlushChecker.h"
#include <map>

HandRank FlushChecker::check(const Hand &hand)
{
    if (isFlush(hand))
    {
        std::cout << "Detected FLUSH\n";
        return HandRank::FLUSH;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FlushChecker::isFlush(const Hand &hand)
{
    if (hand.cards.size() < 5) return false;
    std::map<Suit, int> suitcount;
    for (const auto &card : hand.cards) {
        suitcount[card.suit]++;
    }
    
    for (const auto &entryData : suitcount) {
        if (entryData.second >= 5) return true;
    }
    return false;
}
