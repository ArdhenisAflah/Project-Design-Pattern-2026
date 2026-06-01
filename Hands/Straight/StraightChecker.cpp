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
    bool hasAce = false;
    for (const auto &card : hand.cards) {
        ranks.insert(static_cast<int>(card.rank));
        if (card.rank == Rank::ACE) hasAce = true;
    }
    
    if (ranks.size() < 5) return false;

    // Helper to check consecutive ranks in a sorted vector
    auto checkConsecutive = [](const std::vector<int>& sortedRanks) {
        int consecutive = 1;
        for (size_t i = 1; i < sortedRanks.size(); ++i) {
            if (sortedRanks[i] == sortedRanks[i - 1] + 1) {
                consecutive++;
                if (consecutive >= 5) return true;
            } else {
                consecutive = 1;
            }
        }
        return false;
    };

    // Standard check (Ace is High: 14)
    std::vector<int> vRanks(ranks.begin(), ranks.end());
    if (checkConsecutive(vRanks)) return true;

    // Ace Low check (A, 2, 3, 4, 5)
    if (hasAce) {
        // Create a new set where Ace is treated as 1
        std::set<int> lowRanks;
        for (int r : ranks) {
            if (r == static_cast<int>(Rank::ACE)) lowRanks.insert(1);
            else lowRanks.insert(r);
        }
        std::vector<int> vLowRanks(lowRanks.begin(), lowRanks.end());
        if (checkConsecutive(vLowRanks)) return true;
    }

    return false;
}
