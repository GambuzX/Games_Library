#ifndef HOMEINFO_H
#define HOMEINFO_H

class HomeInfo : TitleInfo {

public:
	vector<Update*> updatesHistory;

	HomeInfo();

	void addUpdate();

	void getCurrentVersion();
};

#endif
