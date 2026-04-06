#pragma once
#include "Hand.h"
#include "Hands/3ofkind/3ofkind.h"
#include "Hands/FlushHouse/FlushHouseChecker.h"
#include "Hands/Flush/FlushChecker.h"
#include "Hands/Pair/PairChecker.h"
class ScoringRule
{
public:
    ScoringRule();
    int scoreHand(const Hand &hand);

private:
    PokerHandChecker *fullhouse =  new FlushChecker();
    int convertRankToScore(HandRank rank);
};