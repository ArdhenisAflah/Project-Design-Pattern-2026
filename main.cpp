#include <iostream>
#include "Hands/Flush/FlushChecker.h"
#include "Hand.h"
int main()
{
    // 1. Siapkan data dummy 'Hand'
    // (Asumsi kelas Hand memiliki constructor atau method untuk isi kartu)
    Hand myHand;
    // Contoh: myHand.addCard(...) atau setup kartu yang bernilai FLUSH

    // 2. Instansiasi FlushChecker menggunakan Polymorphism
    // Kita gunakan pointer ke Parent (PokerHandChecker) agar sesuai prinsip OOP
    PokerHandChecker *checker = new FlushChecker();

    // 3. Eksekusi Test
    std::cout << "Testing Flush Checker..." << std::endl;

    if (checker->check(myHand))
    {
        std::cout << "Result: Ini adalah Flush! (Success)" << std::endl;
    }
    else
    {
        std::cout << "Result: Bukan Flush / Gagal." << std::endl;
    }

    // 4. Cleanup memory
    delete checker;
    return 0;
}