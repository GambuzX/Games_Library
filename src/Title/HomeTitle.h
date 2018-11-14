#ifndef HOMETITLE_H
#define HOMETITLE_H

#include <map>
#include <"Update.h">

class HomeTitle : Title {

private:
	std::vector<Update> titleUpdateHistory;
	std::map<User*, Update> userUpdates;

public:
	void getInfo();

	void getCurrentVersion();

	void updateUserVersion();

	void addTitleUpdate();

	void getStats();
};

#endif
