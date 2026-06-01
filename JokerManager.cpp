#include <iostream>
#include "JokerManager.h"

// void JokerManager::triggerAllJoker(JokerModifieableJoker &modifiable)
void JokerManager::triggerAllJoker()
{
    std::cout << "Joker Manager All Triggered" << std::endl;
    for (auto &item : jokerDeck)
    {
        std::cout << item->getName() << std::endl;
    }
}

void JokerManager::AddJoker(std::unique_ptr<IJokerCard> newCard)
{
    // add joker tyo the vctor
    jokerDeck.push_back(std::move(newCard));
}