// RewardCommand.h
#pragma once

// Forward declaration to avoid circular dependencies
class GameManager; 

enum class RewardTiming {
    START,
    NEXT_BLIND,
    NEXT_ANTE
};

class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    
    // The core execution method
    virtual void execute(GameManager& game) = 0;
    
    // Required to check when this should trigger
    virtual RewardTiming getTiming() const = 0;
};