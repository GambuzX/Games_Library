#ifndef HOMETITLE_H
#define HOMETITLE_H

class HomeTitle : Title {

private:
	vector<Update> updateHistory;
	map<User*, Update> userVersions;
};

#endif
