#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "User.h"

class Subscription {

private:
	double subPrice;

public:
	virtual void chargeUser(User* user) = 0;
};

#endif
