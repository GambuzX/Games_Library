#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H

#include <set>
#include <map>
#include <fstream>
#include "Title\Title.h"
#include "User\User.h"

enum rankingFilter
{
	gender,
	platform,
	age
};

class GameLibrary {

private:
	std::set<Title> titles;
	std::map<User, std::set<Title*>> users;
	static std::map<Title*, double> titlesRevenue;

public:
	void addUser(User* user);

	void removeUser();

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

	static void updateTitleRevenue(Title* title, int double_amount);
};

#endif
