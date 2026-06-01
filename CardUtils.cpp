#include "CardUtils.h"
#include <iostream>  // Needed for std::cout, std::endl
#include <string>    // Needed for std::string
#include <algorithm> // Needed for std::sort

void CardUtils::SortRank(Hand &hand)
{
    // Optimasi Mekanik: Sort kartu dari yang tertinggi ke terendah (UX & Logic)
    std::sort(hand.cards.begin(), hand.cards.end(), [](const Card &a, const Card &b)
              { return static_cast<int>(a.rank) > static_cast<int>(b.rank); });
}

void CardUtils::PrintCards(Hand hand)
{
    std::cout << "=======================" << std::endl;
    int index = 0;
    for (const auto &s : hand.cards)
    {
        std::string rankConverted;
        std::string suitConverted;

        switch (s.suit)
        {
        case Suit::HEARTS:
            suitConverted = "HEARTS";
            break;
        case Suit::DIAMONDS:
            suitConverted = "DIAMOND";
            break;
        case Suit::CLUBS:
            suitConverted = "CLUB";
            break;
        case Suit::SPADES:
            suitConverted = "SPADE";
            break;
        }
        switch (s.rank)
        {
        case Rank::ACE:
            rankConverted = "A";
            break;
        case Rank::TWO:
            rankConverted = "2";
            break;
        case Rank::THREE:
            rankConverted = "3";
            break;
        case Rank::FOUR:
            rankConverted = "4";
            break;
        case Rank::FIVE:
            rankConverted = "5";
            break;
        case Rank::SIX:
            rankConverted = "6";
            break;
        case Rank::SEVEN:
            rankConverted = "7";
            break;
        case Rank::EIGHT:
            rankConverted = "8";
            break;
        case Rank::NINE:
            rankConverted = "9";
            break;
        case Rank::TEN:
            rankConverted = "10";
            break;
        case Rank::JACK:
            rankConverted = "J";
            break;
        case Rank::QUEEN:
            rankConverted = "Q";
            break;
        case Rank::KING:
            rankConverted = "K";
            break;
        }
        if (s.faceDown)
            std::cout << index << "| " << "???" << std::endl;
        else
            std::cout << index << "| " << rankConverted << "::" << suitConverted << std::endl;
        index++;
    }
    std::cout << "=======================" << std::endl;
}