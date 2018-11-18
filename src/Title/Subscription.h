#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "../User/User.h"

class Subscription {

private:
	double subPrice;

public:
	Subscription() { subPrice = 0; };
	Subscription(double sPrice) { subPrice = sPrice; };

	double getSubscriptionPrice() const { return subPrice; };

	virtual double sessionPrice(double sessionHours) = 0;
};

#endif
