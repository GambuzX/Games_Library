#ifndef PROMOTION_H
#define PROMOTION_H

class Promotion {

private:
	Date startDate;
	Date endDate;
	float promoValue;

public:
	Promotion();

	void getStartDate();

	void getEndDate();

	void getPromoValue();
};

#endif
