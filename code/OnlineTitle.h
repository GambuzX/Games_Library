#ifndef ONLINETITLE_H
#define ONLINETITLE_H

class OnlineTitle : Title {

private:
	set<User*> users;
	Subscription* subscription;

public:
	OnlineTitle();

	void ~OnlineTitle();

	virtual void chargeSubscription() = 0;
};

#endif
