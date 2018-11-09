#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

class Subscription {

private:
	double subPrice;

public:
	void chargeUser(User* user) = 0;
};

#endif
