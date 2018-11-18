#ifndef DYNAMICSUBSCRIPTION_H
#define DYNAMICSUBSCRIPTION_H

#include "Subscription.h"

class DynamicSubscription : Subscription {


public:
	DynamicSubscription() : Subscription() {};
	DynamicSubscription(double sPrice) : Subscription(sPrice) {};

	double sessionPrice(double sessionHours) { return floor(sessionHours) * getSubscriptionPrice(); };
};

#endif
