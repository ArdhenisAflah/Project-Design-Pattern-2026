#include <iostream>
#include "RewardRule.h"
int RewardRule::earnMoney(bool win, int score)
{
    if (win)
    {
        // Base reward for winning plus a small bonus based on score
        int baseReward = 4;
        int scoreBonus = score / 50; 
        return baseReward + scoreBonus;
    }
    return 0;
}