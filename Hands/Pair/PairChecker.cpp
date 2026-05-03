#include <iostream>
#include "PairChecker.h"
#include <map>

HandRank PairChecker::check(const Hand &hand)
{
    if (isPair(hand))
    {
        std::cout << "Detected PAIR\n";
        return HandRank::PAIR;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool PairChecker::isPair(const Hand &hand)
{
    if (hand.cards.size() < 2) return false;
    std::map<Rank, int> rankCount;
    for (const auto &card : hand.cards) {
        rankCount[card.rank]++;
    }
    
    for (const auto &entryData : rankCount) {
        if (entryData.second >= 2) return true;
    }
    return false;
}