#include <iostream>
#include "User.h"
#include "..\GameLibrary.h"
#include "..\Utilities\Exceptions.h"

using namespace std;

unsigned int User::nextUserID = 0;

User::User (std::string name, std::string email, int age, Address address) : userID(++nextUserID), createdDate(Date::getCurrentDate()) {
	this->name = name;
	this->email = email;
	this->age = age;
	this->address = address;
}

bool User::addCreditCard(CreditCard cc) {
	creditCards.push_back(cc);
	return true;
}

bool User::hasEnoughMoney(double val) const {
	double amountOwned = 0;

	for (const auto & cc : creditCards)
		// if not expired
		if (Date::getCurrentDate() <= cc.getExpiryDate()) amountOwned += cc.getBalance();

	return amountOwned >= val;
}

bool User::subtractValue(double val)
{
	if (!hasEnoughMoney(val)) return false;

	for (auto & cc : creditCards)
	{
		// If expired, skip card
		if (cc.getExpiryDate() < Date::getCurrentDate()) continue;

		// Remove money
		if (cc.getBalance() >= val)
		{
			try
			{
				cc = cc - val;
			}
			catch (NotEnoughFunds & exc)
			{
				cout << "(" << __func__ << ") Not enough funds: " << exc.getFunds() << endl;
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

bool User::hasTitle(string name, gameLibraryPlatform platform) const {
	set<Title*>::iterator it;
	for (it = purchasedGames->begin(); it != purchasedGames->end(); it++)
		if ((*it)->getName() == name && (*it)->getPlatform() == platform)
			return true;
	return false;
}

bool User::buyTitle(Title* title) {
	// Title repeated 
	if (hasTitle(title)) return false;

	Date currentDate = Date::getCurrentDate();
	double price = title->getCurrentPrice(currentDate);

	// Charge price ; Checks if has enough money
	if (!subtractValue(price)) return false;
	GameLibrary::updateTitleRevenue(title, price);

	try
	{
		title->addNewUser(*this);
	}
	catch (DuplicatedUser)
	{
		cout << "(" << __func__ << ") User " << name << " already owns title " << title->getName() << endl;
		return false;
	}

	// add transaction
	transactions.push_back(Transaction(price, Date::getCurrentDate(), gamePurchase));

	purchasedGames->insert(title);
	return true;
}

bool User::buyTitle(unsigned int titleID) {
	Title * title = GameLibrary::getTitle(titleID);
	if (title == nullptr) return false;

	// Title repeated 
	if (hasTitle(title)) return false;

	Date currentDate = Date::getCurrentDate();
	double price = title->getCurrentPrice(currentDate);

	// Charge price ; Checks if has enough money
	if (!subtractValue(price)) return false;
	GameLibrary::updateTitleRevenue(title, price);

	try
	{
		title->addNewUser(*this);
	}
	catch (DuplicatedUser)
	{
		cout << "(" << __func__ << ") User " << name << " already owns title " << title->getName() << endl;
		return false;
	}

	// add transaction
	transactions.push_back(Transaction(price, Date::getCurrentDate(), gamePurchase));

	purchasedGames->insert(title);
	return true;
}

bool User::buyTitle(std::string name, gameLibraryPlatform platform)
{
	Title * title = GameLibrary::getTitle(name, platform);
	if (title == nullptr) return false;

	// Title repeated 
	if (hasTitle(title)) return false;

	Date currentDate = Date::getCurrentDate();
	double price = title->getCurrentPrice(currentDate);

	// Charge price ; Checks if has enough money
	if (!subtractValue(price)) return false;
	GameLibrary::updateTitleRevenue(title, price);

	try
	{
		title->addNewUser(*this);
	}
	catch (DuplicatedUser)
	{
		cout << "(" << __func__ << ") User " << name << " already owns title " << title->getName() << endl;
		return false;
	}

	// add transaction
	transactions.push_back(Transaction(price, Date::getCurrentDate(), gamePurchase));

	purchasedGames->insert(title);
	return true;
}

bool User::updateTitle(Title* title) {

	if (!hasTitle(title) || !hasEnoughMoney(1)) return false;

	try
	{
		title->updateUserVersion(*this);
	}
	catch (TitleUpToDate)
	{
		cout << "(" << __func__ << ") User " << name << " already has title " << title->getName() << "updated" << endl;
		return false;
	}
	catch (NotHomeTitle)
	{
		cout << "(" << __func__ << ") User " << name << " tried to update Online Title " << title->getName() << endl;
		return false;
	}
	catch (InexistentUser)
	{
		cout << "(" << __func__ << ") User " << name << " does not own title " << title->getName() << endl;
		return false;
	}

	if (!subtractValue(1)) return false;
	GameLibrary::updateTitleRevenue(title, 1);
	transactions.push_back(Transaction(1, Date::getCurrentDate(), homeUpdate));

	return true;
}

bool User::updateTitle(unsigned int titleID) {

	Title * title = GameLibrary::getTitle(titleID);
	if (title == nullptr) return false;

	if (!hasTitle(title) || !hasEnoughMoney(1)) return false;

	try
	{
		title->updateUserVersion(*this);
	}
	catch (TitleUpToDate)
	{
		cout << "(" << __func__ << ") User " << name << " already has title " << title->getName() << "updated" << endl;
		return false;
	}
	catch (NotHomeTitle)
	{
		cout << "(" << __func__ << ") User " << name << " tried to update Online Title " << title->getName() << endl;
		return false;
	}
	catch (InexistentUser)
	{
		cout << "(" << __func__ << ") User " << name << " does not own title " << title->getName() << endl;
		return false;
	}

	if (!subtractValue(1)) return false;
	GameLibrary::updateTitleRevenue(title, 1);
	transactions.push_back(Transaction(1, Date::getCurrentDate(), homeUpdate));

	return true;
}

double User::getTotalTransactionsValue() const
{
	double total = 0;
	for (const auto & trans : transactions) total += trans.getValue();
	return total;
}

string User::getFavoritePlatform() const
{
	map<string, int> platforms;
	for (const auto & title : *purchasedGames)
		platforms[platformEnum2string(title->getPlatform())]++;
	
	pair<string, int> max("", 0);
	for (const auto & entry : platforms)
		if (entry.second > max.second)
			max = entry;

	return max.first;
}

bool User::playGame(Title * title, double duration) {
	if (!hasTitle(title)) return false;
	try
	{
		double playPrice = title->getSubscription()->sessionPrice(duration);
		if (!hasEnoughMoney(playPrice)) return false;
		if (!subtractValue(playPrice)) return false;

		try
		{
			title->addNewSession(*this, Session(duration, Date::getCurrentDate()));
		}
		catch (NotOnlineTitle)
		{
			cout << "(" << __func__ << ") User " << name << " tried to add Session to Home Title " << title->getName() << endl;
			return false;
		}

		GameLibrary::updateTitleRevenue(title, playPrice);
		transactions.push_back(Transaction(playPrice, Date::getCurrentDate(), onlineSubscription));
	}
	catch (NotOnlineTitle)
	{
		try
		{
			title->updateUserVersion(*this);

			// If nothing is thrown, title was updated
			if (!subtractValue(1)) return false;
			GameLibrary::updateTitleRevenue(title, 1);
			transactions.push_back(Transaction(1, Date::getCurrentDate(), homeUpdate));
		}
		catch (TitleUpToDate)
		{
			// Title is up to date, dont need to do anything
			return true;
		}
		catch (NotHomeTitle)
		{
			cout << "(" << __func__ << ") User " << name << " tried to update Online Title " << title->getName() << endl;
			return false;
		}
		catch (InexistentUser)
		{
			cout << "(" << __func__ << ") User " << name << " does not own title " << title->getName() << endl;
			return false;
		}
	}

	return true;
}

bool User::addFriend(User * frnd) {
	set<User*, ComparePtr<User>>::iterator it;
	it = friendsList.find(frnd);

	// Already in friend list
	if (it != friendsList.end()) return false;

	friendsList.insert(frnd);
	return true;
}

bool User::removeFriend(User * frnd) {
	set<User*, ComparePtr<User>>::iterator it;
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