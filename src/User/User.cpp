#include "User.h"
#include "..\GameLibrary.h"
#include "..\Utilities\Exceptions.h"

using namespace std;

unsigned int User::nextUserID = 1;

User::User (std::string name, std::string email, int age, Address address) : userID(nextUserID), createdDate(Date::getCurrentDate()) {
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

bool User::hasTitle(string name) const {
	set<Title*>::iterator it;
	for (it = purchasedGames->begin(); it != purchasedGames->end(); it++)
		if ((*it)->getName() == name)
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

	//TODO ADD USER TO ONLINE STATS OU HOME UPDATES

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

	// add transaction
	transactions.push_back(Transaction(price, Date::getCurrentDate(), gamePurchase));

	purchasedGames->insert(title);
	return true;
}

bool User::buyTitle(std::string name)
{
	Title * title = GameLibrary::getTitle(name);
	if (title == nullptr) return false;

	// Title repeated 
	if (hasTitle(title)) return false;

	Date currentDate = Date::getCurrentDate();
	double price = title->getCurrentPrice(currentDate);

	// Charge price ; Checks if has enough money
	if (!subtractValue(price)) return false;
	GameLibrary::updateTitleRevenue(title, price);

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
		return false;
	}
	catch (NotHomeTitle & excp2)
	{
		return false;
	}
	catch (InexistentUser)
	{
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
		return false;
	}
	catch (NotHomeTitle & excp2)
	{
		return false;
	}
	catch (InexistentUser)
	{
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
		platforms[GameLibrary::getPlatformName(title->getPlatform())]++;
	
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
		// TODO Add game SESSION
		if (!subtractValue(playPrice)) return false;
		GameLibrary::updateTitleRevenue(title, playPrice);
		transactions.push_back(Transaction(playPrice, Date::getCurrentDate(), onlineSubscription));
	}
	catch (NotOnlineTitle & excp)
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
		catch (NotHomeTitle & excp2)
		{
			return false;
		}
		catch (InexistentUser)
		{
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