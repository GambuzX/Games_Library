#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H

#include <set>
#include <map>
#include <fstream>
#include "Title\Title.h"
#include "User\User.h"
#include "Utilities\CompareObj.h"

enum rankingFilter
{
	gender,
	platform,
	age
};

class GameLibrary {
private:
	/*static*/ std::set<Title> titles;
	static std::map<Title*, double, ComparePtr<Title>> titlesRevenue;

	// O MAP JA ORGANIZA USANDO O OPERADOR < RIGHT ????
	std::map<User, std::set<Title*, ComparePtr<Title>>> users;

public:
	void addUser(User * user);
	bool removeUser(User * user);

	void addTitle(Title* title);
	void removeTitle(unsigned int id);

	void loadTitlesFromFile(std::fstream& titleFile);
	void loadUsersFromFile(std::fstream& userFile);

	void updateTitle(Title* title);

	void buildPopularityRanking(rankingFilter filter);
	void averageUserTitles(User* user);
	void favoriteUserPlatform(User* user);
	void userLibraryCost(User* user);
	void buildUserConsumingHabitsList(User* user);

	static void updateTitleRevenue(Title* title, double amount);
	/*
	static Title* getTitle(unsigned int titleID);
	static Title* getTitle(std::string name);
	*/
};

#endif
