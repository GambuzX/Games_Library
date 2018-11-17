#ifndef HOMETITLE_H
#define HOMETITLE_H

#include <sstream>
#include <map>
#include "Title.h"
#include "..\User\User.h"
#include "..\Utilities\CompareObj.h"

class HomeTitle : Title {

private:
	std::vector<Update> titleUpdateHistory;
	std::map<User*, Update, ComparePtr<User>> userUpdates;

public:
	HomeTitle(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);

	const std::vector<Update> & getUpdates() const { return titleUpdateHistory; };
	void getStats() const;

	const Update & getCurrentVersion() const { return titleUpdateHistory.at(titleUpdateHistory.size() - 1); };
	const Update & getCurrentVersion(User * u) const;
	const Update & getCurrentVersion(unsigned int userID) const;
	const Update & getCurrentVersion(std::string name) const;


	void UpdateTitle(Update *);

	void updateUserVersion();
};

#endif
