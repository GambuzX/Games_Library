#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Date.h"

enum TransactionType {
	gamePurchase,
	homeUpdate,
	onlineSubscription
};

class Transaction {

private:
	double value;
	Date date;
	TransactionType type;

public:
	Transaction(double val, Date d, TransactionType type);
	double getValue() const;
	Date getDate() const;
	TransactionType getType() const;
};

#endif
