#ifndef DYNAMICSUBSCRIPTION_H
#define DYNAMICSUBSCRIPTION_H

class DynamicSubscription : Subscription {


public:
	DynamicSubscription();

	void calculateSubPrice(float duration);
};

#endif
