#include <iostream>
#include "ScoringRule.h"
#include "JokerFactory.h"

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

    // Initialize stats for all ranks
    for (int i = 0; i <= (int)HandRank::FLUSH_FIVE; ++i)
    {
        HandRank rank = static_cast<HandRank>(i);
        HandStats base = getBaseStats(rank);
        handStatsMap[rank] = {base.baseChips, base.baseMult, 1}; // Start at level 1
    }
}

int ScoringRule::scoreHand(const Hand &hand)
{
    std::cout << "Calculating hand score...\n";
    HandRank rank = flushfivechecker.check(hand);
    
    HandStats stats = handStatsMap[rank];
    
    // Linear upgrade: +10 chips and +2 mult per level above level 1
    int totalChips = stats.baseChips + (stats.level - 1) * 10;
    int totalMult = stats.baseMult + (stats.level - 1) * 2;

    std::cout << "Hand: Level " << stats.level << " | " << totalChips << " Chips x " << totalMult << " Mult\n";

    int score = totalChips * totalMult;

    jokerManager.triggerAllJoker();
    std::cout << "Final score = " << score << "\n";
    return score;
}

void ScoringRule::upgrade(HandRank rank)
{
    handStatsMap[rank].level++;
    std::cout << "Hand upgraded! New Level: " << handStatsMap[rank].level << "\n";
}

void ScoringRule::AddJoker(const std::string& name)
{
    auto joker = JokerFactory::getInstance().createJoker(name);
    if (joker)
    {
        jokerManager.AddJoker(std::move(joker));
    }
}

HandStats ScoringRule::getBaseStats(HandRank rank)
{
    switch (rank)
    {
    case HandRank::HIGH_CARD: return {5, 1, 1};
    case HandRank::PAIR: return {10, 2, 1};
    case HandRank::TWO_PAIR: return {20, 2, 1};
    case HandRank::THREE_OF_A_KIND: return {30, 3, 1};
    case HandRank::STRAIGHT: return {30, 4, 1};
    case HandRank::FLUSH: return {35, 4, 1};
    case HandRank::FULL_HOUSE: return {40, 4, 1};
    case HandRank::FOUR_OF_A_KIND: return {60, 7, 1};
    case HandRank::STRAIGHT_FLUSH: return {100, 8, 1};
    case HandRank::ROYAL_FLUSH: return {120, 10, 1};
    case HandRank::FIVE_OF_A_KIND: return {120, 12, 1};
    case HandRank::FLUSH_HOUSE: return {140, 14, 1};
    case HandRank::FLUSH_FIVE: return {160, 16, 1};
    default: return {5, 1, 1};
    }
}