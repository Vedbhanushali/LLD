#ifndef AMOUNT_H
#define AMOUNT_H

#include <iostream>
#include <memory>
using namespace std;

class Amount {
    Currency currency;
    double value;
    public:
    Amount(Currency currency, double value);
    Amount add(const Amount& amount); //will add amount to current Amount
    Currency getCurrency() const;
    double getValue() const;
    string print() const;
};

enum Currency {
    USD,
    EUR,
    GBP,
    INR,
    JPY
};

#endif