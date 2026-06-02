#pragma once
#include <iostream>
#include "IJokerCard.h"

class BlueJoker : public IJokerCard
{
public:
    std::string getName() override { return "Blue Joker"; }
    void execute() override { std::cout << "Blue Joker Effect: +10 Chips" << std::endl; }
};