#pragma once
#include "Hand.h"
#include "Jokers/IJokerCard.h"
#include "Jokers/RedJoker.h"
#include <vector>
#include <memory>

class JokerManager
{
private:
    std::vector<std::unique_ptr<IJokerCard>> ownedJokers;

public:
    struct JokerModifieableJoker
    {
        int score;
        int baseChip;
        int baseMult;
    };
    void triggerAllJoker();
    void AddJoker(std::unique_ptr<IJokerCard> newCard);
    int getOwnedCount() const { return (int)ownedJokers.size(); }
};