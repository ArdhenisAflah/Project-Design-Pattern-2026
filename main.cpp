#include <iostream>
#include "Hands/Flush/FlushChecker.h"
#include "Hands/3ofkind/3ofkind.h"
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
    PokerHandChecker *checker2 = new ThreeOfAKindChecker();

    // 3. Eksekusi Test

     std::cout << "Testing 3ofkind Checker..." << std::endl;

    if (checker2->check(myHand))
    {
        std::cout << "Result: Ini adalah 3ofkind! (Success)" << std::endl;
    }
    else
    {
        std::cout << "Result: Bukan 3ofkind / Gagal." << std::endl;
    }
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