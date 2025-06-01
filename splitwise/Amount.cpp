#include "Amount.h"

Amount::Amount(Currency currency, double value) : currency(currency), value(value) {}

Amount Amount::add(const Amount& amount) {
    if (this->currency != amount.currency) {
        throw invalid_argument("Cannot add amounts with different currencies");
    }
    return Amount(this->currency, this->value + amount.value);
}

Currency Amount::getCurrency() const {
    return this->currency;
}

double Amount::getValue() const {
    return this->value;
}

string Amount::print() const {
    string currencyStr;
    switch (this->currency) {
        case USD: currencyStr = "USD"; break;
        case EUR: currencyStr = "EUR"; break;
        case GBP: currencyStr = "GBP"; break;
        case INR: currencyStr = "INR"; break;
        case JPY: currencyStr = "JPY"; break;
    }
    return to_string(this->value) + " " + currencyStr;
}