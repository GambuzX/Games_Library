#include "User.h"
#include <time.h>
#include "..\GameLibrary.h"

using namespace std;

int User::nextUserID = 1;

User::User (std::string name, std::string email, int age, Address address) : userID(nextUserID) {
	this->name = name;
	this->email = email;
	this->age = age;
	this->address = address;
	nextUserID++;
}

bool User::addCreditCard(CreditCard cc) {
	creditCards.push_back(cc);
	return true;
}

bool User::hasEnoughMoney(double val) const {
	double amountOwned = 0;

	time_t theTime = time(NULL);
	struct tm aTime;
	localtime_s(&aTime, &theTime);
	int day = aTime.tm_mday;
	int month = aTime.tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime.tm_year + 1900; // Year is # years since 1900

	for (const auto & cc : creditCards)
		// if not expired
		if (Date(day, month, year) <= cc.getExpiryDate()) amountOwned += cc.getBalance();

	return amountOwned >= val;
}


bool User::subtractValue(double val)
{
	if (!hasEnoughMoney(val)) return false;

	for (auto & cc : creditCards)
	{
		time_t theTime = time(NULL);
		struct tm aTime;
		localtime_s(&aTime, &theTime);
		int day = aTime.tm_mday;
		int month = aTime.tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
		int year = aTime.tm_year + 1900; // Year is # years since 1900

		// If expired, skip card
		if (cc.getExpiryDate() < Date(day, month, year)) continue;

		// Remove money
		if (cc.getBalance() >= val)
		{
			try
			{
				cc = cc - val;
			}
			catch (NotEnoughFunds & exc)
			{
				printf("(%s) Not enough funds: %f", __func__, exc.getFunds());
				return false;
			}
			val = 0;
		}
		else
		{
			val -= cc.getBalance();
			cc.resetFunds();
		}

		// End when value has been charged
		if (val == 0) break;
	}
	return true;
}

bool User::hasTitle(Title* title) const {
	set<Title*>::iterator it;
	it = purchasedGames->find(title);
	if (it == purchasedGames->end()) return false;
	return true;
}

bool User::hasTitle(unsigned int titleID) const {
	set<Title*>::iterator it;
	for (it = purchasedGames->begin(); it != purchasedGames->end(); it++)
		if ((*it)->getTitleID() == titleID)
			return true;
	return false;
}

bool User::buyTitle(Title* title) {
	// Title repeated 
	if (hasTitle(title)) return false;

	time_t theTime = time(NULL);
	struct tm aTime;
	localtime_s(&aTime, &theTime);
	int day = aTime.tm_mday;
	int month = aTime.tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime.tm_year + 1900; // Year is # years since 1900
	Date currentDate = Date(day, month, year);
	double price = title->getCurrentPrice(currentDate);

	// Charge price ; Checks if has enough money
	if (!subtractValue(price)) return false;
	GameLibrary::updateTitleRevenue(title, price);

	purchasedGames->insert(title);
	return true;
}

bool User::buyTitle(unsigned int titleID) {
	// find title to check if repeated
	// if found
		// return false
	// if not enough money
		// return false

	// subtract money
	// add title
	// return true
	return true;
}

bool User::updateTitle(Title* title) {
	// find title
	// if not found
		// return false
	// try
		// title pointer update
		// subtract updates cost to cc
		// update user map
		// increment title static rendimento
	// catch if title is not Home title
		// return false
	// return true
	return true;
}

bool User::updateTitle(unsigned int titleID) {
	// TODO - implement User::updateTitle
	throw "Not yet implemented";
}

bool User::playGame() {
	// Have in account subscriptions
	throw "Not yet implemented";
}

bool User::addFriend(User * frnd) {
	set<User*>::iterator it;
	it = friendsList.find(frnd);

	// Already in friend list
	if (it != friendsList.end()) return false;

	friendsList.insert(frnd);
	return true;
}

bool User::removeFriend(User * frnd) {
	set<User*>::iterator it;
	it = friendsList.find(frnd);

	// Did not find friend
	if (it == friendsList.end()) return false;

	friendsList.erase(it);
	return true;
}

bool User::operator<(const User & usr) const
{
	return userID < usr.getUserID();
}