#include <iostream>
#include "ScoringRule.h"
ScoringRule::ScoringRule()
{
    highcardchecker.setNext(&pairchecker);
    pairchecker.setNext(&twopairchecker);
    twopairchecker.setNext(&threeofkindchecker);
    threeofkindchecker.setNext(&straightchecker);
    straightchecker.setNext(&flushchecker);
    flushchecker.setNext(&fullhousechecker);
    fullhousechecker.setNext(&fourofkindchecker);
    fourofkindchecker.setNext(&straightflushchecker);
    straightflushchecker.setNext(&royalflushchecker);
    royalflushchecker.setNext(&fiveofkindchecker);
    fiveofkindchecker.setNext(&flushhousechecker);
    flushhousechecker.setNext(&flushfivechecker);
}

int ScoringRule::scoreHand(const Hand &hand)
{
    std::cout << "Calculating hand score...\n";
    HandRank rank = highcardchecker.check(hand);
    int score = convertRankToScore(rank);
    std::cout << "Final score = " << score << "\n";
    return score;
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
    default:
        return 5;
    }
}