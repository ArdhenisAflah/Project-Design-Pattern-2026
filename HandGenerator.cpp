#include <iostream>
#include <algorithm> // For std::shuffle
#include <random>    // For std::mt19937, std::random_device
#include "HandGenerator.h"

Hand HandGenerator::generateHand()
{
    std::cout << "Generating cards for player...\n";

    // Build full 52-card deck
    std::vector<Card> deck;
    deck.reserve(52);

    const Suit suits[] = {Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS, Suit::SPADES};
    const Rank ranks[] = {
        Rank::ACE, Rank::TWO, Rank::THREE, Rank::FOUR, Rank::FIVE,
        Rank::SIX, Rank::SEVEN, Rank::EIGHT, Rank::NINE, Rank::TEN,
        Rank::JACK, Rank::QUEEN, Rank::KING};

    for (const Suit &suit : suits)
        for (const Rank &rank : ranks)
            deck.push_back({rank, suit});

    // Shuffle using Mersenne Twister
    std::mt19937 rng(std::random_device{}());
    std::shuffle(deck.begin(), deck.end(), rng);

    // 8 cards
    Hand hand;
    for (int i = 0; i < 8; i++)
<<<<<<< Updated upstream
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
=======
        hand.cards.push_back(deck[i]);

>>>>>>> Stashed changes
    return hand;
}