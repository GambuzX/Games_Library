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
	for (auto & creditC : creditCards)
		if (cc.getNumber() == creditC.getNumber())
			return false;
	creditCards.push_back(cc);
	return true;
}

bool User::removeCreditCard(string creditCardNumber)
{
	for (size_t i = 0; i < creditCards.size(); i++)
		if (creditCardNumber == creditCards.at(i).getNumber()) {
			creditCards.erase(creditCards.begin() + i);
			return true;
		}
	return false;
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
	if (hasTitle(title))
	{
		cout << "(" << __func__ << ") User " << name << " already owns title with ID " << title->getTitleID() << endl;
		return false;
	}

	Date currentDate = Date::getCurrentDate();
	double price = title->getCurrentPrice(currentDate);

	// Charge price ; Checks if has enough money
	if (!subtractValue(price))
	{
		cout << "(" << __func__ << ") Could not subtract value " << price << endl;
		return false;
	}
	GameLibrary::updateTitleRevenue(title, price);
	title->addNewUser(this);
	addTransaction(price, Date::getCurrentDate(), gamePurchase);
	purchasedGames->insert(title);

	return true;
}

bool User::buyTitle(unsigned int titleID) {
	Title * title = GameLibrary::getTitle(titleID);
	if (title == nullptr)
	{
		cout << "(" << __func__ << ") Title with ID " << titleID << " does not exist" << endl;
		return false;
	}

	// Title repeated 
	if (hasTitle(title))
	{
		cout << " User " << name << " already owns title with ID " << titleID << endl;
		//cout << "(" << __func__ << ") User " << name << " already owns title with ID " << titleID << endl;
		return false;
	}

	Date currentDate = Date::getCurrentDate();
	double price = title->getCurrentPrice(currentDate);

	// Charge price ; Checks if has enough money
	if (!subtractValue(price))
	{
		//cout << "(" << __func__ << ") Could not subtract value " << price << endl;
		cout << " User " << name << " does not have enough money: " << price << endl;
		return false;
	}
	GameLibrary::updateTitleRevenue(title, price);
	title->addNewUser(this);
	addTransaction(price, Date::getCurrentDate(), gamePurchase);
	purchasedGames->insert(title);

	return true;
}

bool User::addTitle(unsigned int titleID)
{
    Title * title = GameLibrary::getTitle(titleID);
    if (title == nullptr)
    {
        cout << "(" << __func__ << ") Title with ID " << titleID << " does not exist" << endl;
        return false;
    }

    Date currentDate = Date::getCurrentDate();
    double price = title->getCurrentPrice(currentDate);

    GameLibrary::updateTitleRevenue(title, price);
    title->addNewUser(this);
    purchasedGames->insert(title);

    return false;
}


bool User::buyTitle(std::string name, gameLibraryPlatform platform)
{
	Title * title = GameLibrary::getTitle(name, platform);
	if (title == nullptr)
	{
		cout << "(" << __func__ << ") Title with name " << name << " in platform " << platformEnum2string(platform) << " does not exist" << endl;
		return false;
	}

	// Title repeated 
	if (hasTitle(title))
	{
		cout << "(" << __func__ << ") User " << this->name << " already owns title " << name << " for platform " << platformEnum2string(platform) << endl;
		return false;
	}

	Date currentDate = Date::getCurrentDate();
	double price = title->getCurrentPrice(currentDate);

	// Charge price ; Checks if has enough money
	if (!subtractValue(price))
	{
		cout << "(" << __func__ << ") Could not subtract value " << price << endl;
		return false;
	}
	GameLibrary::updateTitleRevenue(title, price);
	title->addNewUser(this);
	addTransaction(price, Date::getCurrentDate(), gamePurchase);
	purchasedGames->insert(title);

	return true;
}

bool User::updateTitle(Title* title) {

	if (!hasTitle(title))
	{
		cout << "(" << __func__ << ") User " << name << " does not own title with ID " << title->getTitleID() << endl;
		return false;
	}

	if (GameLibrary::isOnlineTitle(title))
	{
		cout << "(" << __func__ << ") Tried to update Online Title with ID " << title->getTitleID() << endl;
		return false;
	}

	if (!title->userNeedsUpdate(this))
	{
		cout << "(" << __func__ << ") User " << name << " already has title with ID " << title->getTitleID() << " updated" << endl;
		return false;
	}

	double updatePrice = title->getCurrentVersion().getUpdatePrice();

	if (!hasEnoughMoney(updatePrice))
	{
		cout << "(" << __func__ << ") User " << name << " does not have enough money to pay the update price: " << updatePrice << endl;
		return false;
	}

	title->updateUserVersion(this);
	if (!subtractValue(updatePrice)) return false;
	GameLibrary::updateTitleRevenue(title, updatePrice);
	addTransaction(updatePrice, Date::getCurrentDate(), homeUpdate);

	return true;
}

bool User::updateTitle(unsigned int titleID) {

	Title * title = GameLibrary::getTitle(titleID);
	if (title == nullptr)
	{
		cout << "(" << __func__ << ") Title with id " << titleID  << " does not exist" << endl;
		return false;
	}

	if (!hasTitle(title))
	{
		cout << "(" << __func__ << ") User " << name << " does not own title with ID " << title->getTitleID() << endl;
		return false;
	}

	if (GameLibrary::isOnlineTitle(title))
	{
		cout << "(" << __func__ << ") Tried to update Online Title with ID " << title->getTitleID() << endl;
		return false;
	}

	if (!title->userNeedsUpdate(this))
	{
		//cout << "(" << __func__ << ") User " << name << " already has title with ID " << title->getTitleID() << " updated" << endl;
		cout << " User " << name << " already has title with ID " << title->getTitleID() << " updated" << endl;
		return false;
	}

	double updatePrice = title->getCurrentVersion().getUpdatePrice();

	if (!hasEnoughMoney(updatePrice))
	{
		//cout << "(" << __func__ << ") User " << name << " does not have enough money to pay the update price: " << updatePrice << endl;
		cout << " User " << name << " does not have enough money to pay the update price: " << updatePrice << endl;
		return false;
	}

	title->updateUserVersion(this);
	if (!subtractValue(updatePrice)) return false;
	GameLibrary::updateTitleRevenue(title, updatePrice);
	addTransaction(updatePrice, Date::getCurrentDate(), homeUpdate);

	return true;
}

CreditCard * User::getCreditCard(std::string creditCardNumber)
{
	for (auto & creditC : creditCards)
		if (creditCardNumber == creditC.getNumber())
			return &creditC;
	return nullptr;
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
	if (!hasTitle(title))
	{
		cout << "(" << __func__ << ") User " << name << " does not own title with ID " << title->getTitleID() << endl;
		return false;
	}

	// If Online Title
	if (GameLibrary::isOnlineTitle(title))
	{
		// Get Subscription Price
		double playPrice = title->getSubscription()->sessionPrice(duration);

		// Check if has enough money
		if (!hasEnoughMoney(playPrice))
		{
			//cout << "(" << __func__ << ") User " << name << " does not have enough money to pay the subscription price: " << playPrice << endl;
			cout << " User " << name << " does not have enough money to pay the subscription price: " << playPrice << endl;
			return false;
		}
		if (!subtractValue(playPrice)) return false;

		title->addNewSession(this, Session(duration, Date::getCurrentDate()));
		GameLibrary::updateTitleRevenue(title, playPrice);
		addTransaction(playPrice, Date::getCurrentDate(), onlineSubscription);
	}
	// If Home Title
	else
	{
		// Title is up to date, don't have to do anything
		if (!title->userNeedsUpdate(this)) return true;

		// Get Update Price
		double updatePrice = title->getCurrentVersion().getUpdatePrice();

		// Check if has enough money
		if (!hasEnoughMoney(updatePrice))
		{
			//cout << "(" << __func__ << ") User " << name << " does not have enough money to pay the update price: " << updatePrice << endl;
			cout << " User " << name << " does not have enough money to pay the update needed price: " << updatePrice << endl;
			return false;
		}

		// Update User Version
		title->updateUserVersion(this);

		// If nothing is thrown, title was updated
		if (!subtractValue(updatePrice)) return false;
		GameLibrary::updateTitleRevenue(title, updatePrice);
		addTransaction(updatePrice, Date::getCurrentDate(), homeUpdate);
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

Title * User::nextAdvertisementTitle(float minimumBuyRate) const
{
	if (wishlist.empty()) return NULL; // TODO ThrOW SOMETHING
	if (wishlist.top().getBuyChance() > minimumBuyRate) return wishlist.top().getTitle();
	priority_queue<WishlistEntry> copy = wishlist;
	copy.pop();
	while (!copy.empty())
	{
		if (copy.top().getBuyChance() > minimumBuyRate) return copy.top().getTitle();
		copy.pop();
	}
	return NULL; // TODO Throw something
}

set<string> User::getPlatforms()
{
	set<string> plats;
	for (const Title * title: *purchasedGames)
		plats.insert(title->getPlatformName());
	return plats;
}

bool User::operator<(const User & usr) const
{
	return userID < usr.getUserID();
}

ostream& operator<<(ostream &os, const User &user)
{
	os << user.getUserID() << " " << user.getName() << endl;
	os << user.getEmail() << " " << user.getAge() << endl;
	user.getAddress().writeAddress(os);

	os << "Credit Cards:" << endl;
	os << user.getCreditCards().size() << endl;
	for (const CreditCard &cc : user.getCreditCards()) {
		os << cc << endl;
	}

	os << "Transactions:" << endl;
	os << user.getTransactions().size() << endl;
	for (Transaction t : user.getTransactions()) {
		t.writeTransaction(os);
	}

	os << "Friends:" << endl;
	os << user.getFriendsList().size() << endl;
	for (const User* f : user.getFriendsList()) {
		os << f->getUserID() << endl;
	}

	return os;
}
