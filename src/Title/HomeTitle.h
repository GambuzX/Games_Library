#ifndef HOMETITLE_H
#define HOMETITLE_H

class HomeTitle : Title {

private:
	vector<Update> titleUpdateHistory;
	map<User*, Update> userUpdates;

public:
	void getInfo();

	void getCurrentVersion();

	void updateUserVersion();

	void addTitleUpdate();

	void getStats();
};

#endif
