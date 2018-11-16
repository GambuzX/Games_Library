#ifndef FIXEDSUBSCRIPTION_H
#define FIXEDSUBSCRIPTION_H

#include "Subscription.h"

class FixedSubscription : Subscription {


public:
	FixedSubscription() : Subscription() {};
	FixedSubscription(double sPrice) : Subscription(sPrice) {};

	void chargeUser(User* user);
};

#endif
