#include <iostream>
#include "HighCardChecker.h"

HandRank HighCardChecker::check(const Hand &hand)
{
    if (isHighCard(hand))
    {
        std::cout << "Detected HIGH CARD\n";
        return HandRank::HIGH_CARD;
    }

    if (nextChecker)
    {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}

bool HighCardChecker::isHighCard(const Hand &hand)
{
    // High Card adalah kondisi default jika ada kartu di tangan 
    // tetapi tidak membentuk kombinasi yang lebih tinggi.
    
    return !hand.cards.empty();
}
