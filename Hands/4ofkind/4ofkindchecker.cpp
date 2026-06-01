#include <iostream>
#include "4ofkindchecker.h"
#include <map>

HandRank FourOfAKindChecker::check(const Hand &hand)
{
    if (isFourOfAKind(hand))
    {
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FourOfAKindChecker::isFourOfAKind(const Hand &hand)
{
    if (hand.cards.size() < 4) return false;
    std::map<Rank, int> rankCount;
    for (const auto &card : hand.cards) {
        rankCount[card.rank]++;
    }
    for (const auto &entryData : rankCount) {
        if (entryData.second >= 4) return true;
    }
    return false;
}