#pragma once
#include <string>
#include "IHandUpgrade.h"

class PlanetCard
{
private:
    std::string name;
    HandRank targetHand;
    int price;

public:
    PlanetCard(std::string n, HandRank rank, int p);
    void use(IHandUpgrade& upgrader);
    std::string getName() const { return name; }
    int getPrice() const { return price; }
    HandRank getTargetHand() const { return targetHand; }
};