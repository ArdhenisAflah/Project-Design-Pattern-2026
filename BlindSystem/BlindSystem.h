#pragma once
#include <memory>
#include "IBlindState.h"

class BlindSystem
{
private:
    std::unique_ptr<IBlindState> currentState;
    int currentAnte = 1;

public:
    BlindSystem();

    void SetState(std::unique_ptr<IBlindState> newState);

    int GetAnte() const { return currentAnte; }
    void IncrementAnte() { currentAnte++; }
    void HandlePlay() { currentState->HandlePlay(this); }
    void HandleSkip() { currentState->HandleSkip(this); }
    IBlindState *GetCurrentState() { return currentState.get(); }
};