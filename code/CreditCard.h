#ifndef CREDITCARD_H
#define CREDITCARD_H

class CreditCard {

private:
	int number;
	Date expiryDate;
	String name;
	float balance;

public:
	void getBalance();

	void getName();

	void getNumber();

	void getExpiryDate();

	void addFunds();

	void removeFunds();

	CreditCard();
};

#endif
