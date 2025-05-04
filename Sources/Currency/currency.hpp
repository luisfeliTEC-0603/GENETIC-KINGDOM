#ifndef CURRENCY_HPP
#define CURRENCY_HPP

class Coins {
private:
    int coins;

public:
    Coins();
    void increasCoins(int numberToIncrease);
    void decreaseCoins(int numberToDecrease);
    int getCoinsAmount() const;
};



#endif