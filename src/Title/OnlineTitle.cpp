#include "OnlineTitle.h"

using namespace std;

OnlineTitle::OnlineTitle(string name, double price, Date releaseDate, ageRange ageR, string platform, string genre, string company, Subscription* subs) : Title(name, price, releaseDate, ageR, platform, genre, company) 
{
	subscription = subs;
}

void OnlineTitle::addUser(User & u)
{
	//titleStats.insert(pair <User*, vector<Session>>(u, {}));
}

void OnlineTitle::getUpdates() {
	// TODO - implement OnlineTitle::getInfo
	throw "Not yet implemented";
}

void OnlineTitle::addUserSession() {
	// TODO - implement OnlineTitle::addUserSession
	throw "Not yet implemented";
}

void OnlineTitle::getStats() {
	// TODO - implement OnlineTitle::getStats
	throw "Not yet implemented";
}
