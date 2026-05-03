#include <iostream>
#include "StraightChecker.h"
#include <set>
#include <vector>
#include <algorithm>

HandRank StraightChecker::check(const Hand &hand)
{
    if (isStraight(hand))
    {
        std::cout << "Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool StraightChecker::isStraight(const Hand &hand)
{
    if (hand.cards.size() < 5) return false;
    std::set<int> ranks;
    for (const auto &card : hand.cards) {
        ranks.insert(static_cast<int>(card.rank));
    }
    if (ranks.size() < 5) return false;
    
    std::vector<int> sortedRanks(ranks.begin(), ranks.end());
    int consecutive = 1;
    for (size_t i = 1; i < sortedRanks.size(); ++i) {
        if (sortedRanks[i] == sortedRanks[i-1] + 1) {
            consecutive++;
            if (consecutive >= 5) return true;
        } else {
            consecutive = 1;
        }
    }
    return false;
}
