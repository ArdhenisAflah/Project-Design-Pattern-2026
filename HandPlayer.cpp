#include <iostream>
#include "HandPlayer.h"
void HandPlayer::playHand(Hand &hand)
{
    std::cout << "Pilih indeks kartu (pisahkan dengan spasi, akhiri dengan -1):";

    int choice;

    while (std::cin >> choice && choice != -1)
    {
        if (choice >= 0 && choice < hand.cards.size())
        {
            this->choosenCards.push_back(hand.cards[choice]);
        }
        else
        {
            std::cout << "Indeks tidak valid!" << std::endl;
        }
    }

    std::cout << std::endl;
}