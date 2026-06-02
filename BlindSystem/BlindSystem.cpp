#include "BlindSystem.h"
#include "ConcreateState.h"
#include "../SkipRewards.h"
#include <chrono>
#include <random>

BlindSystem::BlindSystem()
{
    currentState = std::unique_ptr<SmallBlindState>(new SmallBlindState());
    GenerateNewSkipTags();
}

void BlindSystem::SetState(std::unique_ptr<IBlindState> newState)
{
    currentState = std::move(newState);
}

void BlindSystem::IncrementAnte()
{
    currentAnte++;
    GenerateNewSkipTags();
}

void BlindSystem::GenerateNewSkipTags()
{
    static std::mt19937 rng(static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    
    // Pick two different tag types (0, 1, or 2)
    std::vector<int> types = {0, 1, 2};
    std::shuffle(types.begin(), types.end(), rng);
    
    smallBlindTagType = types[0];
    bigBlindTagType = types[1];
}

std::string BlindSystem::GetCurrentSkipTagName() const
{
    int tagType = 0;
    if (currentState->GetName() == "Small Blind") tagType = smallBlindTagType;
    else if (currentState->GetName() == "Big Blind") tagType = bigBlindTagType;
    else return "No Tag Available";

    switch (tagType)
    {
    case 0: return "Bonus Hand Tag (+1 Hand next blind)";
    case 1: return "Free Card Tag (Added A::SPADE to deck)";
    case 2: return "Investment Tag ($25)";
    default: return "Unknown Tag";
    }
}

std::unique_ptr<RewardCommand> BlindSystem::CreateSkipReward()
{
    int tagType = 0;
    if (currentState->GetName() == "Small Blind") tagType = smallBlindTagType;
    else if (currentState->GetName() == "Big Blind") tagType = bigBlindTagType;
    else return nullptr;

    switch (tagType)
    {
    case 0: return std::make_unique<BonusHandCommand>();
    case 1: return std::make_unique<FreePlayingCardCommand>();
    case 2: return std::make_unique<MoneySkipReward>(25);
    default: return nullptr;
    }
}