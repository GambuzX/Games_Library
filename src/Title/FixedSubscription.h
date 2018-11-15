#ifndef FIXEDSUBSCRIPTION_H
#define FIXEDSUBSCRIPTION_H

#include "Subscription.h"
#include "User.h"

class FixedSubscription : Subscription {


public:
	void chargeUser(User* user);
};

#endif
