#include "OnlineTitle.h"
#include "..\Utilities\Exceptions.h"

using namespace std;

OnlineTitle::OnlineTitle(string name, double price, Date releaseDate, ageRange ageR, string platform, string genre, string company, Subscription* subs) : Title(name, price, releaseDate, ageR, platform, genre, company) 
{
	subscription = subs;
}

void OnlineTitle::addNewUser(User & u)
{
	map<User*, vector<Session>, ComparePtr<User>>::iterator it;
	it = titleStats.find(&u);
	if (it != titleStats.end())
		throw DuplicatetUser(u.getUserID());
	titleStats.insert(pair<User*, vector<Session>>(&u, {}));
}

void OnlineTitle::addNewSession(const User & u, const Session & sess)
{
	map<User*, vector<Session>, ComparePtr<User>>::iterator it;
	it = titleStats.find(const_cast<User*>(&u));
	if (it == titleStats.end())
		throw InexistentUser(u.getUserID());
	it->second.push_back(sess);
}

void OnlineTitle::addNewSession(unsigned int userID, const Session & sess)
{
	for (auto & pair : titleStats)
		if (pair.first->getUserID() == userID) {
			pair.second.push_back(sess);
			return;
		}
	throw InexistentUser(userID);
}

const std::vector<Update>& OnlineTitle::getUpdates() const
{
	throw NotHomeTitle(getTitleID());
}

double OnlineTitle::getStats() const{
	double res = 0.0;
	for (auto pair : titleStats)
		for (size_t i = 0; i < pair.second.size(); i++)
			res += pair.second.at(i).getSessionDuration();
	return res;
}

double OnlineTitle::getStats(const User & u) const
{
	map<User*, vector<Session>, ComparePtr<User>>::const_iterator it;
	it = titleStats.find(const_cast<User*>(&u));
	if (it == titleStats.end())
		throw InexistentUser(u.getUserID());
	double res = 0.0;
	for (size_t i = 0; i < it->second.size(); i++)
		res += it->second.at(i).getSessionDuration();
	return res;
}

double OnlineTitle::getStats(unsigned int userID) const
{
	for (auto & pair : titleStats)
		if (pair.first->getUserID() == userID) {
			double res = 0.0;
			for (size_t i = 0; i < pair.second.size(); i++)
				res += pair.second.at(i).getSessionDuration();
			return res;
		}
	throw InexistentUser(userID);	
}

void OnlineTitle::updateTitle(Update * newUpdate)
{
	throw NotHomeTitle(getTitleID());
}