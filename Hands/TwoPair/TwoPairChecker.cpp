#include <iostream>
#include "TwoPairChecker.h"
#include <map>

HandRank TwoPairChecker::check(const Hand &hand)
{
    if (isTwoPair(hand))
    {
        std::cout << "Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool TwoPairChecker::isTwoPair(const Hand &hand)
{
    if (hand.cards.size() < 4) return false;
    std::map<Rank, int> rankCount;
    for (const auto &card : hand.cards) {
        rankCount[card.rank]++;
    }
    
    int pairs = 0;
    for (const auto &entryData : rankCount) {
        if (entryData.second >= 2) pairs++;
    }
    return pairs >= 2;
}
