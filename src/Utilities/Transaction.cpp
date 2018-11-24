#include "Transaction.h"

Transaction::Transaction(double val, TransactionType t)
{
	value = val;
	date = Date::getCurrentDate();
	type = t;
}

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

std::ostream & operator<<(std::ostream & os, const Transaction & trans)
{
	std::string desc;

	if (trans.getType() == gamePurchase) desc = "Purchased a Title";
	else if (trans.getType() == homeUpdate) desc = "Updated a Home Title";
	else if (trans.getType() == onlineSubscription) desc = "Payed an Online Subscription";

	os << desc << " on " << trans.getDate() << " of value " << trans.getValue() << " .";
	return os;
}

void Transaction::writeTransaction(std::ostream &os) const {
	os << getType() << " " << getDate() << std::endl;
	os << getValue() << std::endl;
}