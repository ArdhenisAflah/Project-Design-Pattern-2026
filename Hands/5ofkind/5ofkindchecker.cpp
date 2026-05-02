#include <iostream>
#include "5ofkindchecker.h"
#include <map>

HandRank FiveOfAKindChecker::check(const Hand &hand)
{
    if (isFiveOfAKind(hand))
    {
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FiveOfAKindChecker::isFiveOfAKind(const Hand &hand)
{
    if (hand.cards.size() < 5)
        return false;

    std::map<Rank, int> rankCount;
    for (const auto &card : hand.cards)
    {
        rankCount[card.rank]++;
    }

    for (const auto &entryData : rankCount)
    {
        if (entryData.second >= 5)
            return true;
    }

    return false;
}
