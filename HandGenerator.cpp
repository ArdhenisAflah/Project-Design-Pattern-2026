#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "HandGenerator.h"
Hand HandGenerator::generateHand()
{
    std::srand(std::time(0));             // Seed with current time
    int randomNum = std::rand() % 13 + 1; // Range 1 to 100
    std::cout << "Generating cards for player...\n";
    Hand hand;

    // untuk random test
    hand.value = randomNum; // dummy: simulate flush
    // untuk fixed value test
    // hand.value = 13;
    return hand;
}