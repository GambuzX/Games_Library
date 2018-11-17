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
	void getStats();

	const Update & getCurrentVersion() const { return titleUpdateHistory.at(titleUpdateHistory.size() - 1); };
	const Update & getCurrentVersion(User * u) const;
	const Update & getCurrentVersion(unsigned int userID) const;
	const Update & getCurrentVersion(std::string name) const;


	void addTitleUpdate(Update & newUpdate);

	void updateUserVersion();

};

class OldUpdate {
private:
	Update oldUpdate;
	Update currentVersion;

public:
	OldUpdate(const Update & oldUp) { oldUpdate = oldUp; };
	OldUpdate(const Update & oldUp, const Update & currUp) { oldUpdate = oldUp; currentVersion = currUp; };
	Update getOldUpdate() const { return oldUpdate; };
	std::string getMessage() const { 
		std::ostringstream oss(oldUpdate.getVersion());
		if (currentVersion == Update())
			return "Tried to add old Update: " + oss.str();
		std::string msg = "Tried to add old Update: " + oss.str() + "while Current Version is: ";
		oss.clear();
		oss << currentVersion.getVersion();
		return msg + oss.str();

	};
};

#endif
