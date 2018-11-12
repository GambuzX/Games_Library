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
	unsigned int start = startDate.getYear() * 10000 + startDate.getMonth() * 100 + startDate.getDay();
	unsigned int end = endDate.getYear() * 10000 + endDate.getMonth() * 100 + endDate.getDay();
	unsigned int current = date.getYera() * 10000 + date.getMonth() * 100 + date.getDay();

	return (current >= start && current <= end);
}