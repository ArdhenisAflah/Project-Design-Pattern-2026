#include "CardUtils.h"

void CardUtils::SortRank(Hand &hand)
{
    // Optimasi Mekanik: Sort kartu dari yang tertinggi ke terendah (UX & Logic)
    std::sort(hand.cards.begin(), hand.cards.end(), [](const Card &a, const Card &b)
              { return static_cast<int>(a.rank) > static_cast<int>(b.rank); });
}