#ifndef ONLINETITLE_H
#define ONLINETITLE_H

#include <map>
#include <vector>
#include "Subscription.h"
#include "..\Utilities\Session.h"
#include "..\Utilities\CompareObj.h"
#include "Title.h"

class OnlineTitle : public Title {

private:
	Subscription* subscription;
	std::map<User*, std::vector<Session>, ComparePtr<User>> titleStats;

public:
	OnlineTitle(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company, Subscription* subs);
	
	const Subscription & getSubscription() const { return *subscription; };
	const std::vector<Update> & getUpdates() const override;
	unsigned int getNumberUsers() const override { return titleStats.size(); };
	double getStats() const override;
	double getStats(const User & u) const;
	double getStats(unsigned int userID) const;

	void updateTitle(Update * newUpdate) override;
	void updateUserVersion(const User & usr) override;

	void addNewUser(User & u) override;

	void addNewSession(const User & u, const Session & sess);
	void addNewSession(unsigned int userID, const Session & sess);


	bool operator<(const Title & t2) const override;

};

#endif
