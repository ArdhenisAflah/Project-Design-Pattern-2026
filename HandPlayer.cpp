#include <iostream>
#include "HandPlayer.h"
#include <algorithm>
void HandPlayer::playHand(Hand &hand)
{
    choosenCards.clear();
    std::cout << "Pilih indeks kartu (pisahkan dengan spasi, akhiri dengan -1):";

    int choice;

    while (std::cin >> choice && choice != -1)
    {
        if (choice >= 0 && choice < (int)hand.cards.size())
        {
            if (this->choosenCards.size() < 5)
            {
                auto item = hand.cards[choice];
                auto isContain = std::find_if(choosenCards.begin(), choosenCards.end(), [item](const Card &card)
                                              { return card.suit == item.suit && card.rank == item.rank; });
                if (isContain == choosenCards.end())
                {
                    this->choosenCards.push_back(hand.cards[choice]);
                }
            }
            else
            {
                std::cout << "Maksimal 5 kartu!" << std::endl;
            }
        }
        else
        {
            std::cout << "Indeks tidak valid!" << std::endl;
        }
    }

    std::cout << std::endl;
}