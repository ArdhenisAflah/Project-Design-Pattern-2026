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
    
    // Add 2 random Jokers
    currentItems.push_back({"Red Joker (Mult +4)", 4, ShopItemType::JOKER});
    currentItems.push_back({"Blue Joker (Chips +10)", 4, ShopItemType::JOKER});

    // Add 2 random Planet Cards
    std::vector<std::pair<std::string, HandRank>> planetOptions = {
        {"Mercury (Pair +10)", HandRank::PAIR},
        {"Venus (Three of a Kind +20)", HandRank::THREE_OF_A_KIND},
        {"Earth (Full House +30)", HandRank::FULL_HOUSE},
        {"Mars (Four of a Kind +40)", HandRank::FOUR_OF_A_KIND},
        {"Jupiter (Flush +25)", HandRank::FLUSH}
    };

    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(planetOptions.begin(), planetOptions.end(), rng);

    currentItems.push_back({planetOptions[0].first, 3, ShopItemType::PLANET_CARD, planetOptions[0].second});
    currentItems.push_back({planetOptions[1].first, 3, ShopItemType::PLANET_CARD, planetOptions[1].second});
}

void Shop::DisplayShop(ScoringRule &scoringRule)
{
    bool inShop = true;
    while (inShop)
    {
        std::cout << "\n========== SHOP ==========\n";
        std::cout << "Your Money: $" << *playerMoney << "\n\n";
        
        for (size_t i = 0; i < currentItems.size(); ++i)
        {
            std::cout << i << ". " << currentItems[i].name << " - $" << currentItems[i].price << "\n";
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
        }
        else if (choice == 4)
        {
            if (*playerMoney >= 5)
            {
                *playerMoney -= 5;
                GenerateShop();
            }
            else
            {
                std::cout << "Not enough money to reroll!\n";
            }
        }
        else if (choice >= 0 && choice < (int)currentItems.size())
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
    ShopItem &item = currentItems[index];
    if (*playerMoney >= item.price)
    {
        *playerMoney -= item.price;
        std::cout << "Purchased: " << item.name << "\n";

        if (item.type == ShopItemType::JOKER)
        {
            // Placeholder: Add to JokerManager in ScoringRule
            // In a full implementation, we'd need to expose JokerManager or use a command
            scoringRule.AddJoker(item.name);
        }
        else if (item.type == ShopItemType::PLANET_CARD)
        {
            scoringRule.UpgradeHand(item.targetHand);
        }

        // Remove item from shop after purchase
        currentItems.erase(currentItems.begin() + index);
    }
    else
    {
        std::cout << "Not enough money!\n";
    }
}