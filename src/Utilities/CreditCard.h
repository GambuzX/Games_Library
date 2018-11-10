#ifndef CREDITCARD_H
#define CREDITCARD_H

class CreditCard {

private:
	string number;
	string holder;
	Date expiryDate;
	double balance;

public:
	void addFunds(double funds);

	void removeFunds(double funds);
};

#endif
