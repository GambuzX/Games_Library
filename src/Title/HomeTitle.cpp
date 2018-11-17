#include "HomeTitle.h"

using namespace std;

HomeTitle::HomeTitle(string name, double price, Date releaseDate, ageRange ageR, string platform, string genre, string company) : Title(name, price, releaseDate, ageR, platform, genre, company) {}

void HomeTitle::getUpdates() {
	// TODO - implement HomeTitle::getInfo
	throw "Not yet implemented";
}

Update HomeTitle::getCurrentVersion() {
	// TODO - implement HomeTitle::getCurrentVersion
	throw "Not yet implemented";
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
