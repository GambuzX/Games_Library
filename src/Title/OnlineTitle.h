#ifndef ONLINETITLE_H
#define ONLINETITLE_H

#include <map>
#include <vector>
#include "Subscription.h"
#include "Session.h"
#include "Title.h"

class OnlineTitle : Title {

private:
	Subscription* subscription;
	std::map<User*, std::vector<Session>> titleStats;

public:
	void getInfo();

	void addUserSession();

	void getStats();
};

#endif
