#pragma once
#include "BlindSystem/BlindSystem.h"
#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"
#include "RewardSystem/RewardCommand.h"
#include "CardUtils.h"

#include "Shop.h"

class GameManager
{
public:
    std::vector<std::unique_ptr<RewardCommand>> pendingCommands; // Command queue

    // Runtime session state
    int totalScore = 0;
    int currentAnte = 1;
    int playerMoney = 4; // Starting money

    void runSession();
    void addReward(std::unique_ptr<RewardCommand> cmd);
    void executeDeferredCommands();

private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    CardUtils cardUtils;
    BlindSystem blindSystem;
    Shop shop;
};