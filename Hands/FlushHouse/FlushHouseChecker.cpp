#include <iostream>
#include <map>
#include "FlushHouseChecker.h"

HandRank FlushHouseChecker::check(const Hand &hand)
{
    if (isFLushHouse(hand))
    {
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool FlushHouseChecker::isFLushHouse(const Hand &hand)
{
    if (hand.cards.size() < 5)
        return false;

    // Group suit
    std::map<Suit, std::vector<Card>> suitGroup;
    for (const auto &card : hand.cards)
    {
        suitGroup[card.suit].push_back(card);
    }

    for (const auto &entryData : suitGroup)
    {
        const std::vector<Card> cards = entryData.second;

        if (cards.size() < 5)
            continue;

        std::map<Rank, int> rankCount;
        for (const auto &card : cards)
        {
            rankCount[card.rank]++;
        }

        bool hasThree = false;
        bool hasTwo = false;

        for (const auto &rankEntry : rankCount)
        {
            if (rankEntry.second >= 3)
                hasThree = true;
            if (rankEntry.second >= 2)
                hasTwo = true;
        }

        if (hasThree && hasTwo)
            return true;
    }

    return false;
}