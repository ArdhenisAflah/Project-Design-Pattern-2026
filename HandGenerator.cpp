#include <iostream>
#include <algorithm>
#include <random>
#include "HandGenerator.h"

HandGenerator::HandGenerator()
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(static_cast<unsigned int>(seed));
    buildDeck();
}

void HandGenerator::buildDeck()
{
    deck.clear();
    deck.reserve(52);

    const Suit suits[] = {Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS, Suit::SPADES};
    const Rank ranks[] = {
        Rank::ACE, Rank::TWO, Rank::THREE, Rank::FOUR, Rank::FIVE,
        Rank::SIX, Rank::SEVEN, Rank::EIGHT, Rank::NINE, Rank::TEN,
        Rank::JACK, Rank::QUEEN, Rank::KING};

    for (const Suit &suit : suits)
        for (const Rank &rank : ranks)
            deck.push_back({rank, suit});

    std::shuffle(deck.begin(), deck.end(), rng);
}

void HandGenerator::resetDeck()
{
    buildDeck();
}

Hand HandGenerator::generateHand()
{
    std::cout << "Generating cards for player...\n";

    if ((int)deck.size() < 8)
        buildDeck();

    Hand hand;
    for (int i = 0; i < 8; i++)
    {
        hand.cards.push_back(deck.back());
        deck.pop_back();
    }
    return hand;
}

Hand HandGenerator::drawCards(int n)
{
    if (deck.empty())
        buildDeck();

    Hand drawn;
    int toDraw = std::min(n, (int)deck.size());
    for (int i = 0; i < toDraw; i++)
    {
        drawn.cards.push_back(deck.back());
        deck.pop_back();
    }
    return drawn;
}
