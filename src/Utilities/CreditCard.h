#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <string>
#include "Date.h"

class CreditCard {

private:
	std::string number;
	std::string holder;
	Date expiryDate;
	double balance;

public:
	CreditCard(std::string n, std::string h, Date exp, double bal);

	std::string getNumber() const { return number; }
	std::string getHolder() const { return holder; }
	Date getExpiryDate() const { return expiryDate; }
	double getBalance() const { return balance; }

	double addFunds(double funds);
	double removeFunds(double funds);

	void resetFunds();

	CreditCard & operator+(const double & val);
	CreditCard & operator-(const double & val);
};

#endif