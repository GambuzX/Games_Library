#ifndef HOMETITLE_H
#define HOMETITLE_H

#include <map>
#include "..\Utilities\Update.h"
#include "Title.h"
#include "..\User\User.h"
#include "..\Utilities\CompareObj.h"

class HomeTitle : Title {

private:
	std::vector<Update> titleUpdateHistory;
	std::map<User*, Update, CompareUserPtr> userUpdates;

public:
	HomeTitle(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);

	void getUpdates();
	void getStats();

	void getCurrentVersion();

	void addTitleUpdate(Update & newUpdate);

	void updateUserVersion();

};

class OldUpdate {
private:
	std::string message;

public:
	OldUpdate() { message = "There are sales overlapping!"; };
	std::string getMessage() const { return message; };
};

#endif
