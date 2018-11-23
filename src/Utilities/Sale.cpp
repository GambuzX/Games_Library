#include "Sale.h"

Sale::Sale(Date start, Date end, double value) {
	startDate = start;
	endDate = end;
	saleFactor = value;
}

Date Sale::getStartDate() const {
	return startDate;
}

Date Sale::getEndDate() const {
	return endDate;
}

double Sale::getSaleFactor() const {
	return saleFactor;
}

bool Sale::isActiveOn(const Date & date) const {
	return startDate <= date && date <= endDate;
}

bool Sale::operator<(const Sale & s2) const
{
	return startDate < s2.getStartDate();
}
std::ostream &operator<<(std::ostream &os, const Sale &s)
{
	os << s.getStartDate() << " " << s.getEndDate() << " " << s.getSaleFactor();
    return os;
}
