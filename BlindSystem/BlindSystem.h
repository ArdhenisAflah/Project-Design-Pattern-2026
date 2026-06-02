#pragma once
#include <memory>
#include "IBlindState.h"

#include <string>

#include "../RewardSystem/RewardCommand.h"

class BlindSystem
{
private:
    std::unique_ptr<IBlindState> currentState;
    int currentAnte = 1;
    int smallBlindTagType = 0;
    int bigBlindTagType = 0;

public:
    BlindSystem();

    void SetState(std::unique_ptr<IBlindState> newState);

    int GetAnte() const { return currentAnte; }
    void IncrementAnte(); 
    void HandlePlay() { currentState->HandlePlay(this); }
    std::unique_ptr<RewardCommand> HandleSkip() { return currentState->HandleSkip(this); }
    IBlindState *GetCurrentState() { return currentState.get(); }

    std::string GetCurrentSkipTagName() const;
    std::unique_ptr<RewardCommand> CreateSkipReward();
    void GenerateNewSkipTags();
};