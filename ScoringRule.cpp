#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule()
{
    flushfivechecker.setNext(&fiveofkindchecker);
    fiveofkindchecker.setNext(&flushhousechecker);
    flushhousechecker.setNext(&royalflushchecker);
    royalflushchecker.setNext(&straightflushchecker);
    straightflushchecker.setNext(&fourofkindchecker);
    fourofkindchecker.setNext(&fullhousechecker);
    fullhousechecker.setNext(&flushchecker);
    flushchecker.setNext(&straightchecker);
    straightchecker.setNext(&threeofkindchecker);
    threeofkindchecker.setNext(&twopairchecker);
    twopairchecker.setNext(&pairchecker);
    pairchecker.setNext(&highcardchecker);

    // Initialize levels
    handLevels[HandRank::HIGH_CARD] = 0;
    handLevels[HandRank::PAIR] = 0;
    handLevels[HandRank::TWO_PAIR] = 0;
    handLevels[HandRank::THREE_OF_A_KIND] = 0;
    handLevels[HandRank::STRAIGHT] = 0;
    handLevels[HandRank::FLUSH] = 0;
    handLevels[HandRank::FULL_HOUSE] = 0;
    handLevels[HandRank::FOUR_OF_A_KIND] = 0;
    handLevels[HandRank::STRAIGHT_FLUSH] = 0;
    handLevels[HandRank::ROYAL_FLUSH] = 0;
    handLevels[HandRank::FIVE_OF_A_KIND] = 0;
    handLevels[HandRank::FLUSH_HOUSE] = 0;
    handLevels[HandRank::FLUSH_FIVE] = 0;
}

int ScoringRule::scoreHand(const Hand &hand)
{
    std::cout << "Calculating hand score...\n";
    HandRank rank = flushfivechecker.check(hand);
    int baseScore = convertRankToScore(rank);
    int levelBonus = handLevels[rank];
    int score = baseScore + levelBonus;

    if (levelBonus > 0)
        std::cout << "Level Bonus: +" << levelBonus << "\n";

    jokerManager.triggerAllJoker();
    std::cout << "Final score = " << score << "\n";
    return score;
}

void ScoringRule::UpgradeHand(HandRank rank)
{
    handLevels[rank] += 15; // Example upgrade value
    std::cout << "Hand upgraded! Current level bonus: " << handLevels[rank] << "\n";
}

void ScoringRule::AddJoker(const std::string& name)
{
    if (name.find("Red") != std::string::npos)
        jokerManager.AddJoker(std::make_unique<RedJoker>());
    // Add logic for Blue Joker etc.
}
int ScoringRule::convertRankToScore(HandRank rank)
{
    switch (rank)
    {
    case HandRank::HIGH_CARD:
        return 1;
    case HandRank::PAIR:
        return 10;
    case HandRank::TWO_PAIR:
        return 20;
    case HandRank::THREE_OF_A_KIND:
        return 30;
    case HandRank::STRAIGHT:
        return 40;
    case HandRank::FLUSH:
        return 50;
    case HandRank::FULL_HOUSE:
        return 60;
    case HandRank::FOUR_OF_A_KIND:
        return 70;
    case HandRank::STRAIGHT_FLUSH:
        return 80;
    case HandRank::ROYAL_FLUSH:
        return 90;
    case HandRank::FIVE_OF_A_KIND:
        return 100;
    case HandRank::FLUSH_HOUSE:
        return 110;
    case HandRank::FLUSH_FIVE:
        return 120;
    default:
        return 5;
    }
}