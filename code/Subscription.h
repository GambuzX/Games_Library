#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

class Subscription {

private:
	float servicePrice;

public:
	Subscription();

	virtual void calculateSubPrice(float duration) = 0;
};

#endif
