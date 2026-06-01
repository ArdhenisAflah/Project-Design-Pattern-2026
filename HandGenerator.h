#pragma once
#include "Hand.h"
#include <random>
#include <chrono>
class HandGenerator
{
public:
    Hand generateHand();
    Hand drawCards(int n);
    void resetDeck();
    HandGenerator();

private:
    std::mt19937 rng;
    std::vector<Card> deck;
    void buildDeck();
};