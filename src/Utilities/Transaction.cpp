#include "Transaction.h"
#include "..\GameLibrary.h"

Transaction::Transaction(double val, TransactionType t, unsigned int id)
{
	value = val;
	date = GameLibrary::getLibraryDate();
	type = t;
	titleID = id;
}

Transaction::Transaction(double val, Date d, TransactionType t, unsigned int id) {
	value = val;
	date = d;
	type = t;
	titleID = id;
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

unsigned int Transaction::getTitleID() const
{
	return titleID;
}

std::ostream & operator<<(std::ostream & os, const Transaction & trans)
{
	std::string desc;

	if (trans.getType() == gamePurchase) desc = "Purchased a  with the ID ";
	else if (trans.getType() == homeUpdate) desc = "Updated a Home Title with the ID ";
	else if (trans.getType() == onlineSubscription) desc = "Payed an Online Subscription of the Title with the ID ";

	os << desc << trans.getTitleID();
	os << " on " << trans.getDate() << " of value " << trans.getValue() << " .";
	return os;
}

bool Transaction::operator<(const Transaction & t2) const
{
	return !(this->date <= t2.getDate());
}

void Transaction::writeTransaction(std::ostream &os) const {
	os << getType() << " " << getDate() << " " << getTitleID() << std::endl;
	os << getValue() << std::endl;
}

