// IBlindState.h
#pragma once
#include <string>
#include "../Hand.h"

#include "../RewardSystem/RewardCommand.h"
#include <memory>

class BlindSystem; // Forward declaration

class IBlindState
{
public:
    virtual ~IBlindState() = default;

    virtual void HandlePlay(BlindSystem *system) = 0;
    virtual std::unique_ptr<RewardCommand> HandleSkip(BlindSystem *system) = 0;

    virtual std::string GetName() const = 0;
    virtual int GetTargetScore() const = 0;

    virtual std::string getEffectDescription() const { return ""; }
    virtual void applyPostPlayEffect(Hand &hand) {}
    virtual Hand maskDisplayHand(const Hand &hand) { return hand; }
};