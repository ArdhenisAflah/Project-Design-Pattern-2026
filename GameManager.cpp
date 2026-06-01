#include <iostream>
#include <string>
#include <algorithm>
#include "GameManager.h"

void GameManager::runSession()
{
    bool gameOver = false;

    while (!gameOver)
    {
        const int MAX_ATTEMPTS = 4;
        int attemptsUsed = 0;
        int accumulatedScore = 0;
        bool blindCleared = false;

        auto *currentBlind = blindSystem.GetCurrentState();
        int targetScore = currentBlind->GetTargetScore();

        std::cout << "\n=== Ante " << blindSystem.GetAnte() << " - "
                  << currentBlind->GetName() << " ===\n";
        std::cout << "Target Score: " << targetScore << "\n";

        std::string effect = currentBlind->getEffectDescription();
        if (!effect.empty())
            std::cout << "[Effect] " << effect << "\n";

        handGenerator.resetDeck();
        Hand currentHand = handGenerator.generateHand();

        while (attemptsUsed < MAX_ATTEMPTS && !blindCleared)
        {
            std::cout << "\nAttempt " << (attemptsUsed + 1) << "/" << MAX_ATTEMPTS
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
                std::cout << "Money gained: " << reward << "\n";

                blindSystem.HandlePlay();
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
                    std::cout << "Hand refilled with " << (int)refill.cards.size() << " new card(s).\n";

                attemptsUsed++;
            }
        }

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
    for (auto &cmd : pendingCommands)
        cmd->execute(*this);
    pendingCommands.clear();
}
