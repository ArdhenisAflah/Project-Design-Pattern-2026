#pragma once
#include "Hand.h"
#include "Hands/FlushHouse/FlushHouseChecker.h"
#include "Hands/Flush/FlushChecker.h"
#include "Hands/Pair/PairChecker.h"
#include "Hands/HighCard/HighCardChecker.h"
#include "Hands/TwoPair/TwoPairChecker.h"
#include "Hands/4ofkind/4ofkindchecker.h"
#include "Hands/3ofkind/3ofkind.h"
#include "Hands/5ofkind/5ofkindchecker.h"
#include "Hands/FlushFive/FlushFiveChecker.h"
#include "Hands/Straight/StraightChecker.h"
#include "Hands/StraightFlush/StraightFlushChecker.h"
#include "Hands/RoyalFlush/RoyalFlushChecker.h"
#include "Hands/FullHouse/FullHouseChecker.h"
#include "JokerManager.h"
class ScoringRule
{
public:
    ScoringRule();
    int scoreHand(const Hand &hand);

private:
    JokerManager jokerManager;
    HighCardChecker highcardchecker;
    PairChecker pairchecker;
    TwoPairChecker twopairchecker;
    ThreeOfAKindChecker threeofkindchecker;
    StraightChecker straightchecker;
    FlushChecker flushchecker;
    FullHouseChecker fullhousechecker;
    FourOfAKindChecker fourofkindchecker;
    StraightFlushChecker straightflushchecker;
    RoyalFlushChecker royalflushchecker;
    FiveOfAKindChecker fiveofkindchecker;
    FlushHouseChecker flushhousechecker;
    FlushFiveChecker flushfivechecker;

    int convertRankToScore(HandRank rank);
};