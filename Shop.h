#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "ScoringRule.h"

enum class ShopItemType
{
    JOKER,
    PLANET_CARD
};

struct ShopItem
{
    std::string name;
    int price;
    ShopItemType type;
    HandRank targetHand; // For Planet Cards
};

class Shop
{
private:
    int* playerMoney;
    std::vector<ShopItem> currentItems;

public:
    Shop();
    Shop(int &money);
    void setMoney(int &money);
    void GenerateShop();
    void DisplayShop(ScoringRule &scoringRule);
    void BuyItem(int index, ScoringRule &scoringRule);
};