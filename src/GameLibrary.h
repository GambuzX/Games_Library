#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H

#include <set>
#include <map>
#include <fstream>
#include "Title.h"
#include "User.h"

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

	void loadTitlesFromFile(fstream& titleFile);

	void loadUsersFromFile(fstream& userFile);

	void updateHomeTitle(HomeTitle* title);

	void buildPopularityRanking(rankingFilter filter);

	void averageUserTitles(User* user);

	void favoriteUserPlatform(User* user);

	void userLibraryCost(User* user);

	void buildUserConsumingHabitsList(User* user);

	static void updateTitleRevenue(Title* title, int double_amount);
};

#endif
