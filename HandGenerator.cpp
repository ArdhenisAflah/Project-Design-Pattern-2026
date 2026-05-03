#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "HandGenerator.h"
Hand HandGenerator::generateHand()
{
    std::cout << "Generating cards for player...\n";
    std::srand(std::time(0)); // Seed with current time
    Hand hand;
    for (int i = 0; i < 8; i++)
    {
        int randomRank = std::rand() % 13 + 1; // Range 1 to 13
        int randomSuit = std::rand() % 4 + 1;  // Range 1 to 4
        Suit suitConverted;
        Rank rankConverted;
        switch (randomSuit)
        {
        case 1:
            suitConverted = Suit::HEARTS;
            break;
        case 2:
            suitConverted = Suit::DIAMONDS;
            break;
        case 3:
            suitConverted = Suit::CLUBS;
            break;
        case 4:
            suitConverted = Suit::SPADES;
            break;
        }

        switch (randomRank)
        {
        case 1:
            rankConverted = Rank::ACE;
            break;
        case 2:
            rankConverted = Rank::TWO;
            break;
        case 3:
            rankConverted = Rank::THREE;
            break;
        case 4:
            rankConverted = Rank::FOUR;
            break;
        case 5:
            rankConverted = Rank::FIVE;
            break;
        case 6:
            rankConverted = Rank::SIX;
            break;
        case 7:
            rankConverted = Rank::SEVEN;
            break;
        case 8:
            rankConverted = Rank::EIGHT;
            break;
        case 9:
            rankConverted = Rank::NINE;
            break;
        case 10:
            rankConverted = Rank::TEN;
            break;
        case 11:
            rankConverted = Rank::JACK;
            break;
        case 12:
            rankConverted = Rank::QUEEN;
            break;
        case 13:
            rankConverted = Rank::KING;
            break;
        }
        hand.cards.push_back({rankConverted, suitConverted});
    }


    // For testing purposes, we will create a hand with a known combination
    // hand.cards.push_back({Rank::ACE, Suit::HEARTS});
    // hand.cards.push_back({Rank::TWO, Suit::DIAMONDS});
    // hand.cards.push_back({Rank::THREE, Suit::CLUBS});
    // hand.cards.push_back({Rank::FOUR, Suit::SPADES});
    // hand.cards.push_back({Rank::FIVE, Suit::HEARTS});

    return hand;
}