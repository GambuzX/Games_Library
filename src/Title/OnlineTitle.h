#ifndef ONLINETITLE_H
#define ONLINETITLE_H

#include <map>
#include <vector>
#include "Subscription.h"
#include "..\Utilities\Session.h"
#include "Title.h"

class OnlineTitle : Title {

private:
	Subscription* subscription;
	// Some kind of ordenation or by address??
	std::map<User*, std::vector<Session>> titleStats;

public:
	OnlineTitle(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company, Subscription* subs);
	
	void addUser(User & u);

	void getInfo();

	void addUserSession();

	void getStats();
};

#endif
