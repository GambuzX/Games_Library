#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H

#include <set>
#include <map>
#include <fstream>
#include "Title\Title.h"
#include "User\User.h"
#include "Utilities\Update.h"
#include "Utilities\CompareObj.h"

enum rankingFilter
{
	gender,
	platform,
	age
};

class GameLibrary {
private:
	static std::set<Title> titles;
	static std::map<Title*, double, ComparePtr<Title>> titlesRevenue;

	std::map<User, std::set<Title*, ComparePtr<Title>>> users;

public:
	void addUser(std::string name, std::string email, int age, Address address);
	void addUser(User * user);
	bool removeUser(User * user);

	void addTitle(Title * title);
	bool removeTitle(unsigned int id);

	void saveGameLibraryToFile(std::fstream& titleFile);
	void loadGameLibraryFromFile(std::fstream& titleFile);

	bool updateTitle(Title* title, Update * update);

	void buildPopularityRanking(rankingFilter filter);
	double averageUserTitles() const;
	std::string favoriteUserPlatform(User* user) const;

	double userLibraryCost(User* user) const;
	double averageUserLibraryCost() const;

	void buildUserConsumingHabitsList(User* user);

	static bool updateTitleRevenue(Title* title, double amount);
	
	static Title* getTitle(unsigned int titleID);
	static Title* getTitle(std::string name);
	
};

#endif
