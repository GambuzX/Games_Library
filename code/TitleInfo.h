#ifndef TITLEINFO_H
#define TITLEINFO_H

class TitleInfo {

private:
	vector<GameSession> playingSessions;

public:
	TitleInfo();

	void getTimePlayed();

	void getLastSession();

	void addGameSession();
};

#endif
