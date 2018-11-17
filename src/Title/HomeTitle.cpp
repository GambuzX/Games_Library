#include "HomeTitle.h"

using namespace std;

HomeTitle::HomeTitle(string name, double price, Date releaseDate, ageRange ageR, string platform, string genre, string company) : Title(name, price, releaseDate, ageR, platform, genre, company) 
{
	titleUpdateHistory.push_back(Update(releaseDate));
}

void HomeTitle::addTitleUpdate(Update & newUpdate)
{
	if (titleUpdateHistory.size() == 0)
		titleUpdateHistory.push_back(newUpdate);
	else if (getCurrentVersion() < newUpdate)
		titleUpdateHistory.push_back(newUpdate);
	else
		throw OldUpdate(newUpdate, getCurrentVersion());
}

void HomeTitle::updateUserVersion() {
	// TODO - implement HomeTitle::updateUserVersion
	throw "Not yet implemented";
}

void HomeTitle::getStats() {
	// TODO - implement HomeTitle::getStats
	throw "Not yet implemented";
}

const Update & HomeTitle::getCurrentVersion(User * u) const
{/*
	map<User*, Update, ComparePtr<User>>::iterator it;
	it = userUpdates.find(u);

	if (it == userUpdates.end()) 
		throw
	return userUpdates.at(begin() + it);*/
}

const Update & HomeTitle::getCurrentVersion(unsigned int userID) const
{
	// TODO: insert return statement here
}

const Update & HomeTitle::getCurrentVersion(std::string name) const
{
	// TODO: insert return statement here
}
