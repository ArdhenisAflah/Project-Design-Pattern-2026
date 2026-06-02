#include "Shop.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

Shop::Shop() : playerMoney(nullptr) {}

Shop::Shop(int &money) : playerMoney(&money) {}

void Shop::setMoney(int &money)
{
    playerMoney = &money;
}

void Shop::GenerateShop()
{
    currentItems.clear();
    currentPlanets.clear();
    
    // Draw unique Jokers from the JokerDeck
    std::vector<std::string> drawnJokers = jokerDeck.drawJokers(2);
    for (const auto& name : drawnJokers)
    {
        currentItems.push_back({name, 4, ShopItemType::JOKER});
    }

    // Add 2 random Planet Cards
    std::vector<std::pair<std::string, HandRank>> planetOptions = {
        {"Mercury (Pair)", HandRank::PAIR},
        {"Venus (Three of a Kind)", HandRank::THREE_OF_A_KIND},
        {"Earth (Full House)", HandRank::FULL_HOUSE},
        {"Mars (Four of a Kind)", HandRank::FOUR_OF_A_KIND},
        {"Jupiter (Flush)", HandRank::FLUSH}
    };

    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(planetOptions.begin(), planetOptions.end(), rng);

    currentPlanets.push_back({planetOptions[0].first, planetOptions[0].second, 3});
    currentPlanets.push_back({planetOptions[1].first, planetOptions[1].second, 3});
}

void Shop::DisplayShop(ScoringRule &scoringRule)
{
    bool inShop = true;
    while (inShop)
    {
        std::cout << "\n========== SHOP ==========\n";
        std::cout << "Your Money: $" << *playerMoney << " | Jokers: " << scoringRule.getJokerCount() << "/5\n\n";
        
        int idx = 0;
        for (const auto& item : currentItems)
        {
            std::cout << idx++ << ". [Joker] " << item.name << " - $" << item.price << "\n";
        }
        for (const auto& planet : currentPlanets)
        {
            std::cout << idx++ << ". [Planet] " << planet.getName() << " - $" << planet.getPrice() << "\n";
        }
        
        std::cout << "4. Reroll ($5)\n";
        std::cout << "-1. Exit Shop\n";
        std::cout << "Choose item to buy: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == -1)
        {
            inShop = false;
            // Return unbought jokers to deck when exiting
            for (const auto& item : currentItems) {
                if (item.type == ShopItemType::JOKER) {
                    jokerDeck.returnJoker(item.name);
                }
            }
        }
        else if (choice == 4)
        {
            if (*playerMoney >= 5)
            {
                *playerMoney -= 5;
                // Return unbought jokers to deck
                for (const auto& item : currentItems) {
                    jokerDeck.returnJoker(item.name);
                }
                GenerateShop();
            }
            else
            {
                std::cout << "Not enough money to reroll!\n";
            }
        }
        else if (choice >= 0 && choice < (int)(currentItems.size() + currentPlanets.size()))
        {
            BuyItem(choice, scoringRule);
        }
        else
        {
            std::cout << "Invalid choice!\n";
        }
    }
}

void Shop::BuyItem(int index, ScoringRule &scoringRule)
{
    if (index < (int)currentItems.size())
    {
        ShopItem &item = currentItems[index];
        if (*playerMoney >= item.price)
        {
            if (scoringRule.getJokerCount() < 5)
            {
                *playerMoney -= item.price;
                std::cout << "Purchased: " << item.name << "\n";
                scoringRule.AddJoker(item.name);
                currentItems.erase(currentItems.begin() + index);
            }
            else
            {
                std::cout << "Joker slots full (Max 5)!\n";
            }
        }
        else
        {
            std::cout << "Not enough money!\n";
        }
    }
    else
    {
        int planetIdx = index - (int)currentItems.size();
        PlanetCard &planet = currentPlanets[planetIdx];
        if (*playerMoney >= planet.getPrice())
        {
            *playerMoney -= planet.getPrice();
            std::cout << "Purchased: " << planet.getName() << "\n";
            planet.use(scoringRule); 
            currentPlanets.erase(currentPlanets.begin() + planetIdx);
        }
        else
        {
            std::cout << "Not enough money!\n";
        }
    }
}