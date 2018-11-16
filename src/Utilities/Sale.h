#ifndef SALE_H
#define SALE_H

#include "Date.h"

class Sale {

private:
	Date startDate;
	Date endDate;
	double saleFactor;
public:
	Sale(Date start, Date end, double val);
	Date getStartDate() const;
	Date getEndDate() const;
	double getSaleFactor() const;
	bool isActiveOn(const Date & date) const;

	bool operator<(const Sale& s2) const;
};

#endif
