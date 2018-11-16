#ifndef HOMETITLE_H
#define HOMETITLE_H

#include <map>
#include "..\Utilities\Update.h"
#include "Title.h"
#include "..\User\User.h"

class HomeTitle : Title {

private:
	std::vector<Update> titleUpdateHistory;
	std::map<User*, Update> userUpdates;

public:
	HomeTitle(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);

	void getInfo();

	void getCurrentVersion();

	void updateUserVersion();

	void addTitleUpdate();

	void getStats();
};

#endif
