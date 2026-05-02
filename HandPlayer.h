#pragma once
#include "Hand.h"
#include <vector>
class HandPlayer
{

private:
    std::vector<Card> choosenCards;

public:
    void playHand(Hand &hand);
    // getter function
    Hand getChoosenHand() const
    {
        Hand handChoosed{1, choosenCards};
        return handChoosed;
    }
};