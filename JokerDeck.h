#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include "Jokers/IJokerCard.h"
#include "Jokers/RedJoker.h"
#include "Jokers/BlueJoker.h"

class JokerDeck
{
private:
    std::vector<std::string> availableJokers;
    std::mt19937 rng;

public:
    JokerDeck()
    {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        rng.seed(static_cast<unsigned int>(seed));
        
        // Initial pool of Jokers (only implemented ones)
        availableJokers = {"Red Joker", "Blue Joker"};
        std::shuffle(availableJokers.begin(), availableJokers.end(), rng);
    }

    std::vector<std::string> drawJokers(int count)
    {
        std::vector<std::string> drawn;
        int toDraw = std::min(count, (int)availableJokers.size());
        for (int i = 0; i < toDraw; ++i)
        {
            drawn.push_back(availableJokers.back());
            availableJokers.pop_back();
        }
        return drawn;
    }

    void returnJoker(std::string name)
    {
        availableJokers.push_back(name);
        std::shuffle(availableJokers.begin(), availableJokers.end(), rng);
    }

    bool isEmpty() const { return availableJokers.empty(); }
};