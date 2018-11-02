#ifndef FIXEDSUBSCRIPTION_H
#define FIXEDSUBSCRIPTION_H

class FixedSubscription : Subscription {


public:
	FixedSubscription();

	void calculateSubPrice(float duration);
};

#endif
