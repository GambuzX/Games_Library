#ifndef GAMESLIBRARY_H
#define GAMESLIBRARY_H

class GamesLibrary {

private:
	set<User*> users;
	set<Title*> titles;

public:
	vector<User*> getUsersWithTitle(Title* title);

	vector<Title*> identifyMostProfitableTitles();

	float getAverageTitlesPerUser();

	vector<string> getMostPopularPlatforms();

	float getAverageLibraryCost();

	void listConsumingHabits(User* user);

	vector<Title*> getPopularityRanking(string filter);

	void ~GamesLibrary();

	void addUser();

	void removeUser();

	void addTitle();

	void removeTitle();

	void getUserStatistics(User* user);
};

#endif
