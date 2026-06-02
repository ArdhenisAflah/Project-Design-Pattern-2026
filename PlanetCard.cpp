#include "PlanetCard.h"
#include <iostream>

PlanetCard::PlanetCard(std::string n, HandRank rank, int p) 
    : name(n), targetHand(rank), price(p) {}

void PlanetCard::use(IHandUpgrade& upgrader)
{
    std::cout << "Using Planet Card: " << name << "\n";
    upgrader.upgrade(targetHand);
}