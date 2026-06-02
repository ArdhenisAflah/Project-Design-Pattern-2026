#include <iostream>
#include <algorithm>
#include <chrono>
#include "ConcreateState.h"

// ── Small Blind ──────────────────────────────────────────────
void SmallBlindState::HandlePlay(BlindSystem *system)
{
    system->SetState(std::make_unique<BigBlindState>());
}

std::unique_ptr<RewardCommand> SmallBlindState::HandleSkip(BlindSystem *system)
{
    auto reward = system->CreateSkipReward();
    system->SetState(std::make_unique<BigBlindState>());
    return reward;
}

// ── Big Blind ────────────────────────────────────────────────
static std::unique_ptr<IBlindState> randomBoss()
{
    static std::mt19937 rng(
        static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    switch (rng() % 3)
    {
    case 0:  return std::make_unique<TheHookBoss>();
    case 1:  return std::make_unique<TheWallBoss>();
    default: return std::make_unique<TheWheelBoss>();
    }
}

void BigBlindState::HandlePlay(BlindSystem *system)
{
    system->SetState(randomBoss());
}

std::unique_ptr<RewardCommand> BigBlindState::HandleSkip(BlindSystem *system)
{
    auto reward = system->CreateSkipReward();
    system->SetState(randomBoss());
    return reward;
}

// ── Boss Blind Base ──────────────────────────────────────────
void BossBlindBase::HandlePlay(BlindSystem *system)
{
    system->IncrementAnte();
    system->SetState(std::make_unique<SmallBlindState>());
}

std::unique_ptr<RewardCommand> BossBlindBase::HandleSkip(BlindSystem *system)
{
    // Boss blind usually can't be skipped in Balatro, but following instructions
    auto reward = system->CreateSkipReward();
    system->IncrementAnte();
    system->SetState(std::make_unique<SmallBlindState>());
    return reward;
}

// ── The Hook ─────────────────────────────────────────────────
TheHookBoss::TheHookBoss()
{
    rng.seed(static_cast<unsigned>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}

void TheHookBoss::applyPostPlayEffect(Hand &hand)
{
    int toRemove = std::min(2, (int)hand.cards.size());
    for (int i = 0; i < toRemove; i++)
    {
        int idx = rng() % hand.cards.size();
        std::cout << "[The Hook] Discarded: card at slot " << idx << "\n";
        hand.cards.erase(hand.cards.begin() + idx);
    }
}

// ── The Wall ─────────────────────────────────────────────────
// No extra behaviour — higher target score is the only effect.

// ── The Wheel ────────────────────────────────────────────────
TheWheelBoss::TheWheelBoss()
{
    rng.seed(static_cast<unsigned>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}

Hand TheWheelBoss::maskDisplayHand(const Hand &hand)
{
    Hand masked = hand;
    for (auto &card : masked.cards)
    {
        if (rng() % 7 == 0)
            card.faceDown = true;
    }
    return masked;
}