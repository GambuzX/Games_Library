#include "CreditCard.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

CreditCard::CreditCard(std::string n, std::string h, Date exp, double bal) {
	if (bal < 0) throw NegativeFunds(bal);
	number = n;
	holder = h;
	expiryDate = exp;
	balance = bal;
}

double CreditCard::addFunds(double funds) {
	balance += funds;
	return balance;
}

double CreditCard::removeFunds(double funds) {
	if (balance < funds) throw NotEnoughFunds(funds);
	balance -= funds;
	return balance;
}

void CreditCard::resetFunds() { balance = 0; }

CreditCard & CreditCard::operator+(const double & val) {
	addFunds(val);
	return *this;
}


CreditCard & CreditCard::operator-(const double & val) {
	try {
		removeFunds(val);
	}
	catch (NotEnoughFunds) {
		throw;
	}
	return *this;
}

ostream &operator<<(ostream &os, const CreditCard &cc)
{
	os << cc.getNumber() << " " << cc.getHolder() << " " << cc.getExpiryDate() << " " << cc.getBalance();

    return os;
}
