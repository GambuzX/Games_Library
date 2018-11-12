#include "Transaction.h"

Transaction::Transaction(double val, Date d, TransactionType t) {
	value = val;
	date = d;
	type = t;
}

double Transaction::getValue() const {
	return value;
}

Date Transaction::getDate() const {
	return date;
}

TransactionType Transaction::getType() const {
	return type;
}