#include <iostream>
#include <string>
#include <algorithm>
#include "GameManager.h"

void GameManager::runSession()
{
    std::cout << "=== Run Started ===\n";
    Hand hand = handGenerator.generateHand();

    // Optimasi Mekanik: Sort kartu dari yang tertinggi ke terendah (UX & Logic)
    std::sort(hand.cards.begin(), hand.cards.end(), [](const Card &a, const Card &b) {
        return static_cast<int>(a.rank) > static_cast<int>(b.rank);
    });

    std::cout << "HAND GENERATED (Sorted): " << std::endl;

    std::cout << "=======================" << std::endl;
    for (size_t i = 0; i < hand.cards.size(); ++i)
    {
        const auto &s = hand.cards[i];
        std::string rankConverted;
        std::string suitConverted;

        switch (s.suit)
        {
        case Suit::HEARTS:
            suitConverted = "H";
            break;
        case Suit::DIAMONDS:
            suitConverted = "D";
            break;
        case Suit::CLUBS:
            suitConverted = "C";
            break;
        case Suit::SPADES:
            suitConverted = "S";
            break;
        }
        switch (s.rank)
        {
        case Rank::ACE:
            rankConverted = "A";
            break;
        case Rank::TWO:
            rankConverted = "2";
            break;
        case Rank::THREE:
            rankConverted = "3";
            break;
        case Rank::FOUR:
            rankConverted = "4";
            break;
        case Rank::FIVE:
            rankConverted = "5";
            break;
        case Rank::SIX:
            rankConverted = "6";
            break;
        case Rank::SEVEN:
            rankConverted = "7";
            break;
        case Rank::EIGHT:
            rankConverted = "8";
            break;
        case Rank::NINE:
            rankConverted = "9";
            break;
        case Rank::TEN:
            rankConverted = "10";
            break;
        case Rank::JACK:
            rankConverted = "J";
            break;
        case Rank::QUEEN:
            rankConverted = "Q";
            break;
        case Rank::KING:
            rankConverted = "K";
            break;
        }
        std::cout << "[" << i << "] " << rankConverted << "::" << suitConverted << std::endl;
    }
    std::cout << "=======================" << std::endl;

    handPlayer.playHand(hand);
    Hand choosedHand = handPlayer.getChoosenHand();

    // Optimasi Mekanik: Sort kartu pilihan agar rapi saat dinilai
    std::sort(choosedHand.cards.begin(), choosedHand.cards.end(), [](const Card &a, const Card &b) {
        return static_cast<int>(a.rank) > static_cast<int>(b.rank);
    });

    std::cout << "YOU CHOOSED : " << std::endl;
    std::cout << "=======================" << std::endl;
    for (const auto &s : choosedHand.cards)
    {
        std::string rankConverted;
        std::string suitConverted;

        switch (s.suit)
        {
        case Suit::HEARTS:
            suitConverted = "H";
            break;
        case Suit::DIAMONDS:
            suitConverted = "D";
            break;
        case Suit::CLUBS:
            suitConverted = "C";
            break;
        case Suit::SPADES:
            suitConverted = "S";
            break;
        }
        switch (s.rank)
        {
        case Rank::ACE:
            rankConverted = "A";
            break;
        case Rank::TWO:
            rankConverted = "2";
            break;
        case Rank::THREE:
            rankConverted = "3";
            break;
        case Rank::FOUR:
            rankConverted = "4";
            break;
        case Rank::FIVE:
            rankConverted = "5";
            break;
        case Rank::SIX:
            rankConverted = "6";
            break;
        case Rank::SEVEN:
            rankConverted = "7";
            break;
        case Rank::EIGHT:
            rankConverted = "8";
            break;
        case Rank::NINE:
            rankConverted = "9";
            break;
        case Rank::TEN:
            rankConverted = "10";
            break;
        case Rank::JACK:
            rankConverted = "J";
            break;
        case Rank::QUEEN:
            rankConverted = "Q";
            break;
        case Rank::KING:
            rankConverted = "K";
            break;
        }
        std::cout << rankConverted << "::" << suitConverted << std::endl;
    }
    std::cout << "=======================" << std::endl;

    int score = scoringRule.scoreHand(choosedHand);
    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);
    std::cout << "Money gained: " << reward << "\n";

    std::cout << "=== Run Ended ===\n";
}