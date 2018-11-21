#include <iostream>
#include "GameLibrary.h"
#include "Utilities\Exceptions.h"

using namespace std;

set<Title*, ComparePtr<Title>> GameLibrary::titles;
map<Title*, double, ComparePtr<Title>> GameLibrary::titlesRevenue;

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

bool GameLibrary::addTitle(Title * title) {
	bool repeated = false;
	for (const auto t : titles)
		if (t->getName() == title->getName() && t->getPlatform() == title->getPlatform())
		{
			repeated = true;
			break;
		}
	if (repeated) return false;
	titles.insert(title);
	return true;
}

bool GameLibrary::removeTitle(Title * title) {
	std::set<Title*, ComparePtr<Title>>::iterator it;
	it = titles.find(title);
	if (it == titles.end()) return false;
	titles.erase(it);
	return true;
}

bool GameLibrary::removeTitle(unsigned int id) {
	std::set<Title*, ComparePtr<Title>>::iterator it;
	for (it = titles.begin(); it != titles.end(); it++)
		if ((*it)->getTitleID() == id)
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
		cout << "(" << __func__ << ") Game Library tried to update Online Title " << title->getName() << endl;
		return false;
	}
	catch (OldUpdate & excp)
	{
		cout << "(" << __func__ << ") Tried to update title " << title->getName() << " from Current version " << excp.getCurrentVersion().getVersion();
		cout << " to Older version " << excp.getOldUpdate().getVersion() << endl;
		return false;
	}
	return true;
}

void GameLibrary::buildGlobalPopularityRanking(ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR) {
	
	map<int, const Title*> rankedList;
	
	// Search for all the titles that match and organize them by popularity
	for (const Title * title : titles)
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		int numberOfPlayers = title->getNumberUsers(ageR);
		rankedList.insert(pair<int, const Title*>(numberOfPlayers, title));
	}

	os << "Titles Popularity Ranking" << endl << endl;
	os << "Filters used:\n" << "Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << ", Age Group = " << ageR.minAge << " to " << ageR.maxAge << endl << endl;

	os << "N" << " " << "ID" << " " << "Name" << " " << "Popularity" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		// TODO FORMAT THE OUTPUT
		os << counter << ". " << entry.second->getTitleID() << " " << entry.second->getName() << " " << entry.first << endl;
		counter++;
	}	
}

void GameLibrary::buildGlobalRevenueRanking(ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR)
{
	map<double, const Title*> rankedList;

	// Search for all the titles that match and organize them by revenue
	for (Title * title : titles)
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		map<Title*, double, ComparePtr<Title>>::iterator it = titlesRevenue.find(title);
		rankedList.insert(pair<double, const Title*>((*it).second, title));
	}

	os << "Titles Revenue Ranking" << endl << endl;
	os << "Filters used:\n" << "Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << ", Age Group = " << ageR.minAge << " to " << ageR.maxAge << endl << endl;

	os << "N" << " " << "ID" << " " << "Name" << " " << "Revenue" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		// TODO FORMAT THE OUTPUT
		os << counter << ". " << entry.second->getTitleID() << " " << entry.second->getName() << " " << entry.first << endl;
		counter++;
	}
}

void GameLibrary::buildUserMostPlayedTitlesRanking(std::ostream & os, User * usr, gameLibraryPlatform platform, gameLibraryGenre genre)
{
	map<double, const Title*> rankedList;

	// Search for all the user titles that match and organize them by time played
	for (Title * title : *(usr->getPurchasedGames()))
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		try
		{
			double timePlayed = title->getTimePlayed(usr);
			rankedList.insert(pair<double, const Title*>(timePlayed, title));
		}
		catch (NotOnlineTitle) { continue; }
		catch (InexistentUser) { continue; }
	}

	os << "User Most Played Titles" << endl << endl;
	os << "Filters used:\n" << "Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << endl << endl;

	os << "N" << " " << "ID" << " " << "Name" << " " << "Hours Played" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		// TODO FORMAT THE OUTPUT
		os << counter << ". " << entry.second->getTitleID() << " " << entry.second->getName() << " " << entry.first << endl;
		counter++;
	}
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

double GameLibrary::onlineTitlesPlayTime(User * user) const
{
	double total = 0;
	for (const Title * title : *(user->getPurchasedGames()))
	{
		try
		{
			double time = title->getTimePlayed(user);
			total += time;
		}
		catch (NotOnlineTitle)
		{
			cout << "(" << __func__ << ") Game Library tried to get time played from Home Title " << title->getName() << endl;
			continue;
		}
		catch (InexistentUser)
		{
			cout << "(" << __func__ << ") Tried to get time played from title " << title->getName() << " for User ";
			cout << user->getName() << " who does not own the title" << endl;
			continue;
		}
	}
	return total;
}

void GameLibrary::buildUserConsumingHabitsList(User* user, ostream & os, ConsumingHabitsFilter chFilter)
{
	bool purchases = false, updates = false, subscriptions = false;
	switch (chFilter)
	{
	case pus: purchases = true;	updates = true;	subscriptions = true; break;
	case p:	purchases = true; break;
	case u:	updates = true;	break;
	case s:	subscriptions = true; break;
	case pu: purchases = true; updates = true; break;
	case ps: purchases = true; subscriptions = true; break;
	case us: updates = true; subscriptions = true; break;
	default: break;
	}

	os << "Consuming Habits of User " << user->getName() << ", ID = " << user->getUserID() << " :" << endl << endl;

	double purchasesTotal = 0, updatesTotal = 0, subsTotal = 0;
	int updatesCount = 0, subsCount = 0;
	for (const auto & trans : user->getTransactions())
	{
		if (trans.getType() == gamePurchase)
		{
			purchasesTotal += trans.getValue();
			if (purchases)
				os << trans << endl;
		}
		else if (trans.getType() == homeUpdate)
		{
			updatesCount++; 
			updatesTotal += trans.getValue();
			if (updates)
				os << trans << endl;
		}
		else if (trans.getType() == onlineSubscription)
		{
			subsCount++;
			subsTotal += trans.getValue();
			if (subscriptions)
				os << trans << endl;
		}
	}

	os << endl;
	if (purchases)
	{
		os << "Number of Titles Owned: " << (*(user->getPurchasedGames())).size() << endl;
		os << "Total spent purchasing Titles: " << purchasesTotal << endl;
	}
	if (updates)
	{
		os << "Number of Home Title Updates: " << updatesCount << endl;
		os << "Total spent updating Home Titles: " << updatesTotal << endl;
	}
	if (subscriptions)
	{
		os << "Number of Subscription Fees Payed: " << subsCount << endl;
		os << "Total spent paying Subscription Fees: " << subsTotal << endl;
	}
	if (purchases && updates && subscriptions)
	{
		os << "User Library Cost: " << (purchasesTotal + updatesTotal + subsTotal) << endl;
		os << "Account created on " << user->getCreationDate() << endl;
		os << "Favorite User Platform: " << favoriteUserPlatform(user) << endl;
		os << "Online Titles Playtime: " << onlineTitlesPlayTime(user) << endl;
		os << "Number of Friends: " << (user->getFriendsList()).size() << endl;
	}
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
		if (title->getTitleID() == titleID)
			return const_cast<Title*>(title);
	return nullptr;
}

Title * GameLibrary::getTitle(std::string name, gameLibraryPlatform platform)
{
	for (auto & title : titles)
		if (title->getName() == name && title->getPlatform() == platform)
			return const_cast<Title*>(title);
	return nullptr;
}

bool GameLibrary::userBelongsToAgeRange(const User * usr, ageRange ageR)
{
	return (usr->getAge() >= ageR.minAge && usr->getAge() <= ageR.maxAge);
}

bool GameLibrary::isOnlineTitle(Title * title)
{
	try
	{
		title->getSubscription();
	}
	catch (NotOnlineTitle)
	{
		return false;
	}
	return true;
}