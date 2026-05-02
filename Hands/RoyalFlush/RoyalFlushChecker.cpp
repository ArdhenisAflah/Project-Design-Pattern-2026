#include <iostream>
#include "RoyalFlushChecker.h"
#include <map>
#include <set>

HandRank RoyalFlushChecker::check(const Hand &hand)
{
    if (isRoyalFlush(hand))
    {
        std::cout << "Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }
    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool RoyalFlushChecker::isRoyalFlush(const Hand &hand)
{
    // cek >= 5

    if (hand.cards.size() < 5)
        return false;

    // grouping suit

    std::map<Suit, std::vector<Card>> SuitGroup;

    for (const auto &card : hand.cards)
    {
        SuitGroup[card.suit].push_back(card);
    }

    for (const auto &entryData : SuitGroup)
    {
        // hitung card masing masing suit
        std::vector<Card> cards = entryData.second;

        // butuh suit at least 5
        if (cards.size() < 5)
            continue;

        std::set<Rank> ranks;

        // cek juga rank. (A,K,Q,J,10)
        for (const auto &card : cards)
        {
            ranks.insert(card.rank);
        }

        // check here for  (A,K,Q,J,10)
        if (ranks.count(Rank::ACE) &&
            ranks.count(Rank::KING) &&
            ranks.count(Rank::QUEEN) &&
            ranks.count(Rank::JACK) &&
            ranks.count(Rank::TEN))
        {
            return true;
        }
    }

    return false;
}