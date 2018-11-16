#ifndef DYNAMICSUBSCRIPTION_H
#define DYNAMICSUBSCRIPTION_H

#include "Subscription.h"

class DynamicSubscription : Subscription {


public:
	DynamicSubscription() : Subscription() {};
	DynamicSubscription(double sPrice) : Subscription(sPrice) {};

	void chargeUser(User* user);
};

#endif
