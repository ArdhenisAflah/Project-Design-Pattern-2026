#include <iostream>
#include <string>
#include <algorithm>
#include "GameManager.h"

void GameManager::runSession()
{
    bool gameOver = false;
    shop.setMoney(playerMoney); // Link money to shop

    while (!gameOver)
    {
        auto *currentBlind = blindSystem.GetCurrentState();
        bool isBoss = (currentBlind->GetName().find("Boss") != std::string::npos);
        
        std::cout << "\n=== Ante " << blindSystem.GetAnte() << " - " << currentBlind->GetName() << " ===\n";
        
        // Skip Blind Option (only for non-boss blinds)
        if (!isBoss)
        {
            std::cout << "Skip Tag for this Blind: " << blindSystem.GetCurrentSkipTagName() << "\n";
            std::cout << "1. Play Blind\n";
            std::cout << "2. Skip Blind (Get Tag)\n";
            std::cout << "Choice: ";
            int skipChoice;
            std::cin >> skipChoice;
            if (skipChoice == 2)
            {
                auto reward = blindSystem.HandleSkip();
                if (reward)
                {
                    addReward(std::move(reward));
                    std::cout << "Blind skipped! Tag collected.\n";
                }
                continue; // Move to next blind
            }
        }

        // Execute commands that trigger at the start of a blind
        executeDeferredCommands();

        const int BASE_ATTEMPTS = 4;
        int maxAttempts = BASE_ATTEMPTS + bonusHands;
        int attemptsUsed = 0;
        int accumulatedScore = 0;
        bool blindCleared = false;
        
        int targetScore = currentBlind->GetTargetScore();
        std::cout << "Target Score: " << targetScore << " | Hands: " << maxAttempts << "\n";

        std::string effect = currentBlind->getEffectDescription();
        if (!effect.empty())
            std::cout << "[Effect] " << effect << "\n";

        handGenerator.resetDeck();
        Hand currentHand = handGenerator.generateHand();

        while (attemptsUsed < maxAttempts && !blindCleared)
        {
            std::cout << "\nAttempt " << (attemptsUsed + 1) << "/" << maxAttempts
                      << " | Accumulated: " << accumulatedScore << "/" << targetScore << "\n";

            CardUtils::SortRank(currentHand);
            Hand displayHand = currentBlind->maskDisplayHand(currentHand);
            CardUtils::PrintCards(displayHand);

            handPlayer.playHand(currentHand);
            Hand choosedHand = handPlayer.getChoosenHand();
            CardUtils::SortRank(choosedHand);

            int score = scoringRule.scoreHand(choosedHand);
            accumulatedScore += score;

            std::cout << "Score this play: " << score
                      << " | Total: " << accumulatedScore << "/" << targetScore << "\n";

            if (accumulatedScore >= targetScore)
            {
                std::cout << "Success! Target reached.\n";
                blindCleared = true;

                int reward = rewardRule.earnMoney(true, accumulatedScore);
                playerMoney += reward;
                std::cout << "Money gained: " << reward << " | Current Money: $" << playerMoney << "\n";

                blindSystem.HandlePlay();

                // Show Shop after clearing blind
                shop.GenerateShop();
                shop.DisplayShop(scoringRule); 
            }
            else
            {
                // Remove played cards from hand
                for (const Card &played : choosedHand.cards)
                {
                    auto it = std::find_if(currentHand.cards.begin(), currentHand.cards.end(),
                        [&played](const Card &c) {
                            return c.rank == played.rank && c.suit == played.suit;
                        });
                    if (it != currentHand.cards.end())
                        currentHand.cards.erase(it);
                }

                // Apply boss effect (e.g. The Hook discards 2 more)
                currentBlind->applyPostPlayEffect(currentHand);

                // Refill only for the cards that were played
                int playedCount = (int)choosedHand.cards.size();
                Hand refill = handGenerator.drawCards(playedCount);
                for (const Card &c : refill.cards)
                    currentHand.cards.push_back(c);

                if (!refill.cards.empty())
                    std::cout << "Hand refill: " << (int)refill.cards.size() << " card(s).\n";

                attemptsUsed++;
            }
        }

        // Reset bonus hands after the blind
        bonusHands = 0;

        if (!blindCleared)
        {
            std::cout << "GAME OVER: Failed to clear the blind.\n";
            gameOver = true;
        }
    }

    std::cout << "=== Run Ended ===\n";
}

void GameManager::addReward(std::unique_ptr<RewardCommand> cmd)
{
    pendingCommands.push_back(std::move(cmd));
}

void GameManager::executeDeferredCommands()
{
    // Execute all commands in queue
    for (auto &cmd : pendingCommands)
    {
        cmd->execute(*this);
    }
    pendingCommands.clear();
}
