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