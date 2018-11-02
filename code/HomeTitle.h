#ifndef HOMETITLE_H
#define HOMETITLE_H

class HomeTitle : Title {

public:
	vector<Update> updatesHistory;

	HomeTitle();

	void addUpdate();
};

#endif
