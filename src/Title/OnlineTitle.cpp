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

const vector<Session> * OnlineTitle::getAllUserSessions(User * usr) const
{
	map<User*, vector<Session>, ComparePtr<User>>::const_iterator it;
	it = titleStats.find(const_cast<User*>(usr));
	if (it == titleStats.end())
		throw InexistentUser(usr->getUserID());
	return &(it->second);
}

const map<User*, vector<Session>, ComparePtr<User>> OnlineTitle::getAllUsersLastNSessions(unsigned int n) const
{
	map<User*, vector<Session>, ComparePtr<User>> userMap;
	for (const auto & usr : titleStats)
		userMap.insert(pair<User*, vector<Session>>(usr.first, getLastNUserSessions(usr.first, n)));
	return userMap;
}

const vector<Session> OnlineTitle::getLastNUserSessions(User * usr, int n) const
{
	map<User*, vector<Session>, ComparePtr<User>>::const_iterator it;
	it = titleStats.find(const_cast<User*>(usr));
	if (it == titleStats.end())
		throw InexistentUser(usr->getUserID());

	vector<Session> sessions;
	vector<Session>::const_reverse_iterator rit;
	for (rit = it->second.rbegin(); rit != it->second.rend() && n > 0; rit++)
		sessions.push_back(*rit);
	return sessions;
}

const map<User*, const vector<Session>*, ComparePtr<User>> OnlineTitle::getTop3PlayersSessions() const
{
	multimap<double, User*, DecrescentOrder<double>> userTimes;
	for (const auto & usr : titleStats)
		userTimes.insert(pair<double, User*>(getStats(usr.first), usr.first));

	map<User*, const vector<Session>*, ComparePtr<User>> returnMap;
	multimap<double, User*, DecrescentOrder<double>>::reverse_iterator rit;
	int inserted = 0;
	for (rit = userTimes.rbegin(); rit != userTimes.rend() && inserted < 3; rit++)
		returnMap.insert(pair<User*, const vector<Session>*>(rit->second, getAllUserSessions(rit->second)));

	return returnMap;
}

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

	int total = 0;
	for (auto &it : titleStats)
		total += it.second.size();

	os << total << endl;

	for (auto &it : titleStats) {
	    for (Session &s : it.second)
	        os << it.first->getUserID() << " " << s;
	}
}