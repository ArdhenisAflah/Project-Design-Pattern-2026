#include <iostream>
#include "FullHouseChecker.h"
#include <map>

HandRank FullHouseChecker::check(const Hand &hand)
{
    if (isFullHouse(hand))
    {
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FullHouseChecker::isFullHouse(const Hand &hand)
{
    if (hand.cards.size() < 5) return false;
    std::map<Rank, int> rankCount;
    for (const auto &card : hand.cards) {
        rankCount[card.rank]++;
    }
    
    bool hasThreeOfAKind = false;
    bool hasPair = false;
    
    for (const auto &entryData : rankCount) {
        if (entryData.second >= 3) hasThreeOfAKind = true;
        else if (entryData.second >= 2) hasPair = true;
    }
    
    return hasThreeOfAKind && hasPair;
}
