#ifndef DYNAMICSUBSCRIPTION_H
#define DYNAMICSUBSCRIPTION_H

#include "Subscription.h"

class DynamicSubscription : Subscription {


public:
	void chargeUser(User* user);
};

#endif
