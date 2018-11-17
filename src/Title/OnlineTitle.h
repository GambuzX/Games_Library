#ifndef ONLINETITLE_H
#define ONLINETITLE_H

#include <map>
#include <vector>
#include "Subscription.h"
#include "..\Utilities\Session.h"
#include "..\Utilities\CompareObj.h"
#include "Title.h"

class OnlineTitle : Title {

private:
	Subscription* subscription;
	std::map<User*, std::vector<Session>, ComparePtr<User>> titleStats;

public:
	OnlineTitle(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company, Subscription* subs);
	
	void getUpdates();
	void getStats();

	void addUser(User & u);

	void addUserSession();

};

#endif
