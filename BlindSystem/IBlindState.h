// IBlindState.h
#pragma once
#include <string>
#include "../Hand.h"

class BlindSystem; // Forward declaration

class IBlindState
{
public:
    virtual ~IBlindState() = default;

    virtual void HandlePlay(BlindSystem *system) = 0;
    virtual void HandleSkip(BlindSystem *system) = 0;

    virtual std::string GetName() const = 0;
    virtual int GetTargetScore() const = 0;

    virtual std::string getEffectDescription() const { return ""; }
    virtual void applyPostPlayEffect(Hand &hand) {}
    virtual Hand maskDisplayHand(const Hand &hand) { return hand; }
};