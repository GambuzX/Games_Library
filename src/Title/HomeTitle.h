#ifndef HOMETITLE_H
#define HOMETITLE_H

#include <sstream>
#include <map>
#include "Title.h"
#include "..\Utilities\Exceptions.h"
#include "..\Utilities\CompareObj.h"

class HomeTitle : Title {

private:
	std::vector<Update> titleUpdateHistory;
	std::map<User*, Update, ComparePtr<User>> userUpdates;

public:
	HomeTitle(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);
	
	void addNewUser(User & u);

	const std::vector<Update> & getUpdates() const { return titleUpdateHistory; };
	unsigned int getNumberUsers() const { return userUpdates.size(); };
	double getStats() const;

	const Update & getCurrentVersion() const { return titleUpdateHistory.at(titleUpdateHistory.size() - 1); };
	const Update & getCurrentUserVersion(const User & u) const;
	const Update & getCurrentUserVersion(unsigned int userID) const;
	//const Update & getCurrentUserVersion(std::string name) const;


	void updateTitle(Update * newUpdate);

	void updateUserVersion(const User & u);
	void updateUserVersion(unsigned int userID);
	//void updateUserVersion(std::string name);

};

#endif
