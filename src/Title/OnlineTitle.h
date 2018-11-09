#ifndef ONLINETITLE_H
#define ONLINETITLE_H

class OnlineTitle : Title {

private:
	Subscription* subscription;
	map<User*, vector<Session>> titleStats;
};

#endif
