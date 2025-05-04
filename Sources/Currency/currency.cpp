#include "currency.hpp"

Coins:: Coins() {
    coins = 500; // Inicial coins value
}

void Coins::increasCoins(int numberToIncrease) {
    this->coins += numberToIncrease;
}

void Coins::decreaseCoins(int numberToDecrease) {
    this->coins -= numberToDecrease;
}

int Coins::getCoinsAmount() const{
    return this->coins;
}