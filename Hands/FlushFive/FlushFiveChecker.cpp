#include <iostream>
#include "FlushFiveChecker.h"
#include <map>

HandRank FlushFiveChecker::check(const Hand &hand)
{
    if (isFlushFiveChecker(hand))
    {
        std::cout << "Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }

    return HandRank::HIGH_CARD;
}

bool FlushFiveChecker::isFlushFiveChecker(const Hand &hand)
{

    if (hand.cards.size() < 5)
        return false;

    // mapping, kelompokkan berdasarkan rank
    std::map<Rank, std::vector<Card>> rankGroups;
    for (const auto &card : hand.cards)
    {
        rankGroups[card.rank].push_back(card);
    }

    for (const auto &entrydata : rankGroups)
    {
        const std::vector<Card> &cards = entrydata.second;

        if (cards.size() < 5)
            continue;

        std::map<Suit, int> suitCount;
        for (const auto &card : cards)
        {
            suitCount[card.suit]++;
        }

        for (const auto &entryData : suitCount)
        {
            if (entryData.second >= 5)
            {
                return true;
            }
        }
    }
    return false;
}
