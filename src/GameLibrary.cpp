#include "GameLibrary.h"

using namespace std;

void GameLibrary::addUser(User * user) {
	users.insert(pair<User, set<Title*, ComparePtr<Title>>>(*user, set<Title*, ComparePtr<Title>>()));
}

bool GameLibrary::removeUser(User * user) {
	map<User, set<Title*, ComparePtr<Title>>>::iterator it;

	it = users.find(*user);
	if (it == users.end()) return false;
	users.erase(it);
	return true;
}

void GameLibrary::addTitle(Title* title) {
	// TODO - implement GameLibrary::addTitle
	throw "Not yet implemented";
}

void GameLibrary::removeTitle(unsigned int id) {
	// TODO - implement GameLibrary::removeTitle
	throw "Not yet implemented";
}

void GameLibrary::loadTitlesFromFile(std::fstream& titleFile) {
	// TODO - implement GameLibrary::loadTitlesFromFile
	throw "Not yet implemented";
}

void GameLibrary::loadUsersFromFile(std::fstream& userFile) {
	// TODO - implement GameLibrary::loadUsersFromFile
	throw "Not yet implemented";
}

void GameLibrary::updateTitle(Title* title) {
	// TODO - implement GameLibrary::updateHomeTitle
	throw "Not yet implemented";
}

void GameLibrary::buildPopularityRanking(rankingFilter filter) {
	// TODO - implement GameLibrary::buildPopularityRanking
	throw "Not yet implemented";
}

void GameLibrary::averageUserTitles(User* user) {
	// TODO - implement GameLibrary::averageUserTitles
	throw "Not yet implemented";
}

void GameLibrary::favoriteUserPlatform(User* user) {
	// TODO - implement GameLibrary::favoriteUserPlatform
	throw "Not yet implemented";
}

void GameLibrary::userLibraryCost(User* user) {
	// TODO - implement GameLibrary::userLibraryCost
	throw "Not yet implemented";
}

void GameLibrary::buildUserConsumingHabitsList(User* user) {
	// TODO - implement GameLibrary::buildUserConsumingHabitsList
	throw "Not yet implemented";
}

void GameLibrary::updateTitleRevenue(Title* title, double amount) {
	// TODO - implement GameLibrary::updateTitleRevenue
	throw "Not yet implemented";
}

/*
Title * GameLibrary::getTitle(unsigned int titleID)
{
	for (auto & title : titles)
		if (title.getTitleID() == titleID)
			return &title;
	return NULL;
}

Title * GameLibrary::getTitle(std::string name)
{
	for (auto & title : titles)
		if (title.getName() == name)
			return &title;
	return NULL;
}
*/
