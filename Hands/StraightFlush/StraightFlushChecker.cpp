#include <iostream>
#include "StraightFlushChecker.h"
#include <map>
#include <set>
#include <vector>
#include <algorithm>

HandRank StraightFlushChecker::check(const Hand &hand)
{
    if (isStraightFlush(hand))
    {
        std::cout << "Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool StraightFlushChecker::isStraightFlush(const Hand &hand)
{
    if (hand.cards.size() < 5) return false;
    std::map<Suit, std::set<int>> suitRanks;
    for (const auto &card : hand.cards) {
        suitRanks[card.suit].insert(static_cast<int>(card.rank));
    }
    for (const auto &entry : suitRanks) {
        if (entry.second.size() < 5) continue;
        std::vector<int> sortedRanks(entry.second.begin(), entry.second.end());
        int consecutive = 1;
        for (size_t i = 1; i < sortedRanks.size(); ++i) {
            if (sortedRanks[i] == sortedRanks[i-1] + 1) {
                consecutive++;
                if (consecutive >= 5) return true;
            } else {
                consecutive = 1;
            }
        }
    }
    return false;
}
