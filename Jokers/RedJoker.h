#pragma once
#include "IJokerCard.h"
#include <string>

class RedJoker : public IJokerCard
{
private:
    int power;

public:
    RedJoker(int p = 5) : power(p) {}

    std::string getName() override
    {
        return "Red Joker";
    }

    void execute() override
    {
        // Red Joker logic
    }
};