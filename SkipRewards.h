#pragma once
#include "RewardSystem/RewardCommand.h"
#include "GameManager.h"
#include <iostream>

class BonusHandCommand : public RewardCommand {
public:
    void execute(GameManager& game) override {
        game.bonusHands += 1;
        std::cout << "[Tag Executed] Bonus Hand Tag: +1 Hand for this blind!\n";
    }
    RewardTiming getTiming() const override { return RewardTiming::NEXT_BLIND; }
};

class FreePlayingCardCommand : public RewardCommand {
public:
    void execute(GameManager& game) override {
        // Add a random card to the deck (e.g. Ace of Spades)
        Card newCard = {Rank::ACE, Suit::SPADES};
        game.getHandGenerator().addCardToDeck(newCard);
        std::cout << "[Tag Executed] Free Playing Card Tag: Added A::SPADE to deck!\n";
    }
    RewardTiming getTiming() const override { return RewardTiming::NEXT_BLIND; }
};

class MoneySkipReward : public RewardCommand {
    int amount;
public:
    MoneySkipReward(int a) : amount(a) {}
    void execute(GameManager& game) override {
        game.playerMoney += amount;
        std::cout << "[Tag Executed] Received $" << amount << "\n";
    }
    RewardTiming getTiming() const override { return RewardTiming::NEXT_BLIND; }
};
