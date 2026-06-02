#include <iostream>
#include "JokerManager.h"

// void JokerManager::triggerAllJoker(JokerModifieableJoker &modifiable)
void JokerManager::triggerAllJoker()
{
    std::cout << "Joker Manager All Triggered" << std::endl;
    for (auto &item : ownedJokers)
    {
        std::cout << "Triggering: " << item->getName() << std::endl;
        item->execute();
    }
}

void JokerManager::AddJoker(std::unique_ptr<IJokerCard> newCard)
{
    ownedJokers.push_back(std::move(newCard));
}