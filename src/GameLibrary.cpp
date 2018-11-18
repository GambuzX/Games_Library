#include "GameLibrary.h"
#include "Utilities\Exceptions.h"

using namespace std;

void GameLibrary::addUser(std::string name, std::string email, int age, Address address)
{
	users.insert(pair<User, set<Title*, ComparePtr<Title>>>(User(name, email, age, address), set<Title*, ComparePtr<Title>>()));
}

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

void GameLibrary::addTitle(Title * title) {
	titles.insert(*title);
}

bool GameLibrary::removeTitle(unsigned int id) {
	std::set<Title>::iterator it;
	for (it = titles.begin(); it != titles.end(); it++)
		if (it->getTitleID() == id)
			break;
	if (it == titles.end()) return false;
	titles.erase(it);
	return true;
}

void GameLibrary::saveGameLibraryToFile(std::fstream& titleFile)
{

}

void GameLibrary::loadGameLibraryFromFile(std::fstream& titleFile)
{

}

bool GameLibrary::updateTitle(Title* title, Update * update) {
	try
	{
		title->updateTitle(update);
	}
	catch (NotHomeTitle)
	{
		return false;
	}
	return true;
}

void GameLibrary::buildPopularityRanking(rankingFilter filter) {
	// TODO - implement GameLibrary::buildPopularityRanking
	throw "Not yet implemented";
}

double GameLibrary::averageUserTitles() const{
	double total = 0;
	for (const auto & user : users) total += user.second.size();
	return total / users.size();
}

string GameLibrary::favoriteUserPlatform(User* user) const {
	return user->getFavoritePlatform();
}

double GameLibrary::userLibraryCost(User* user) const {
	return user->getTotalTransactionsValue();
}

double GameLibrary::averageUserLibraryCost() const {
	double total = 0;
	for (const auto & user : users) total += userLibraryCost((User *)&user.first);
	return total / users.size();
}

void GameLibrary::buildUserConsumingHabitsList(User* user) {
	// TODO - implement GameLibrary::buildUserConsumingHabitsList
	throw "Not yet implemented";
}

bool GameLibrary::updateTitleRevenue(Title* title, double amount) {
	map<Title*, double, ComparePtr<Title>>::iterator it;
	it = titlesRevenue.find(title);
	if (it == titlesRevenue.end()) return false;
	(*it).second += amount;
	return true;
}

Title * GameLibrary::getTitle(unsigned int titleID)
{
	for (auto & title : titles)
		if (title.getTitleID() == titleID)
			return const_cast<Title*>(&title);
	return NULL;
}

Title * GameLibrary::getTitle(std::string name)
{
	for (auto & title : titles)
		if (title.getName() == name)
			return const_cast<Title*>(&title);
	return NULL;
}

