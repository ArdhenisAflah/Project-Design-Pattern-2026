#include <iostream>
#include "3ofkind.h"
#include <map>

HandRank ThreeOfAKindChecker::check(const Hand &hand)
{
    if (isThreeOfAKind(hand))
    {
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool ThreeOfAKindChecker::isThreeOfAKind(const Hand &hand)
{
    if (hand.cards.size() < 3) return false;
    std::map<Rank, int> rankCount;
    for (const auto &card : hand.cards) {
        rankCount[card.rank]++;
    }
    for (const auto &entryData : rankCount) {
        if (entryData.second >= 3) return true;
    }
    return false;
}