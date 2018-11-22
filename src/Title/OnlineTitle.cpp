#include "OnlineTitle.h"
#include "..\Utilities\Exceptions.h"
#include <algorithm>

using namespace std;

OnlineTitle::OnlineTitle(string name, double price, Date releaseDate, ageRange ageR, gameLibraryPlatform platform, gameLibraryGenre genre, string company, Subscription* subs) : Title(name, price, releaseDate, ageR, platform, genre, company)
{
	subscription = subs;
}

void OnlineTitle::addNewUser(User * u)
{
	map<User*, vector<Session>, ComparePtr<User>>::iterator it;
	it = titleStats.find(u);
	if (it != titleStats.end())
		throw DuplicatedUser(u->getUserID());
	titleStats.insert(pair<User*, vector<Session>>(u, {}));
}

void OnlineTitle::addNewSession(const User * u, const Session & sess)
{
	map<User*, vector<Session>, ComparePtr<User>>::iterator it;
	it = titleStats.find(const_cast<User*>(u));
	if (it == titleStats.end())
		throw InexistentUser(u->getUserID());
	it->second.push_back(sess);
	sort(it->second.begin(), it->second.end());
}

void OnlineTitle::addNewSession(unsigned int userID, const Session & sess)
{
	for (auto & pair : titleStats)
		if (pair.first->getUserID() == userID) {
			pair.second.push_back(sess);
			sort(pair.second.begin(), pair.second.end());
			return;
		}
	throw InexistentUser(userID);
}

const std::vector<Update>& OnlineTitle::getUpdates() const
{
	throw NotHomeTitle(getTitleID());
}

unsigned int OnlineTitle::getNumberUsers(ageRange ageR) const
{
	unsigned int total = 0;
	for (const auto & ref : titleStats)
		if (ref.first->getAge() >= ageR.minAge && ref.first->getAge() <= ageR.maxAge)
			total++;
	return total;
}

double OnlineTitle::getStats() const{
	double res = 0.0;
	for (auto pair : titleStats)
		for (size_t i = 0; i < pair.second.size(); i++)
			res += pair.second.at(i).getSessionDuration();
	return res;
}

double OnlineTitle::getStats(const User * u) const
{
	map<User*, vector<Session>, ComparePtr<User>>::const_iterator it;
	it = titleStats.find(const_cast<User*>(u));
	if (it == titleStats.end())
		throw InexistentUser(u->getUserID());
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
/*
const std::map<User*, std::vector<Session>, ComparePtr<User>>& OnlineTitle::getLastNSessions(unsigned int n) const
{
	if (titleStats.size() == 0)
	{
		// TODO: create exception
		throw;
	}
	pair<User*, Session> lastSess;
	vector<Session> res;
	for (auto pair : titleStats){
		if (pair.second.size() != 0 && lastSess.second.getDate() == Date())
		{
			lastSess.second = pair.second.at(pair.second.size() - 1);
			lastSess.first = pair.first;
		}
		else if (!(lastSess.second.getDate() == Date()) && pair.second.at(pair.second.size() - 1).getDate() < lastSess.second.getDate())
		{
			lastSess.second = pair.second.at(pair.second.size() - 1);
			lastSess.first = pair.first;
		}
	}
}
*/
void OnlineTitle::updateTitle(Update * newUpdate)
{
	throw NotHomeTitle(getTitleID());
}

void OnlineTitle::updateUserVersion(const User * usr)
{
	throw NotHomeTitle(getTitleID());
}

void OnlineTitle::displayTitleInfo(std::ostream &os)
{
	Title::displayTitleInfo(os);
	os << 0 << endl;
	os << "Subscription Info:" << endl;
	os << subscription->getSubscriptionPrice() << " " << subscription->isFixedSubscription() << endl;
	os << "Sessions:" << endl;
	os << titleStats.size() << endl;

	for (auto &it : titleStats) {
	    for (Session &s : it.second)
	        os << it.first->getUserID() << " " << s;
	}

}

/*
bool OnlineTitle::operator<(const Title & t2) const
{
	return getTitleID() < t2.getTitleID();
}
*/