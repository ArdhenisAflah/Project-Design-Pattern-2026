#pragma once
#include <random>
#include "IBlindState.h"
#include "BlindSystem.h"

class SmallBlindState : public IBlindState
{
public:
    std::string GetName() const override { return "Small Blind"; }
    int GetTargetScore() const override { return 10; }

    void HandlePlay(BlindSystem *system) override;
    std::unique_ptr<RewardCommand> HandleSkip(BlindSystem *system) override;
};

class BigBlindState : public IBlindState
{
public:
    std::string GetName() const override { return "Big Blind"; }
    int GetTargetScore() const override { return 30; }

    void HandlePlay(BlindSystem *system) override;
    std::unique_ptr<RewardCommand> HandleSkip(BlindSystem *system) override;
};

// Base for all boss blinds — shared transition logic
class BossBlindBase : public IBlindState
{
public:
    void HandlePlay(BlindSystem *system) override;
    std::unique_ptr<RewardCommand> HandleSkip(BlindSystem *system) override;
};

// The Hook: discards 2 random cards from hand after every played hand
class TheHookBoss : public BossBlindBase
{
    std::mt19937 rng;
public:
    TheHookBoss();
    std::string GetName() const override { return "Boss Blind - The Hook"; }
    int GetTargetScore() const override { return 60; }
    std::string getEffectDescription() const override { return "Discards 2 random cards after every played hand"; }
    void applyPostPlayEffect(Hand &hand) override;
};

// The Wall: extra large blind (2x target score)
class TheWallBoss : public BossBlindBase
{
public:
    std::string GetName() const override { return "Boss Blind - The Wall"; }
    int GetTargetScore() const override { return 120; }
    std::string getEffectDescription() const override { return "Extra large blind (2x target score)"; }
};

// The Wheel: 1 in 7 cards drawn face down
class TheWheelBoss : public BossBlindBase
{
    std::mt19937 rng;
public:
    TheWheelBoss();
    std::string GetName() const override { return "Boss Blind - The Wheel"; }
    int GetTargetScore() const override { return 60; }
    std::string getEffectDescription() const override { return "1 in 7 cards are drawn face down"; }
    Hand maskDisplayHand(const Hand &hand) override;
};
