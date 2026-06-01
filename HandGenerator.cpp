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
        hand.cards.push_back(deck[i]);

    return hand;
}