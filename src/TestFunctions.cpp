#include <iostream>
#include <limits>
#include "Utilities\Date.h"
#include "Interface\ConsoleFunctions.h"
#include "Interface\Input.h"
#include "GameLibrary.h"
#include "Title/HomeTitle.h"
#include "Title/OnlineTitle.h"
#include "Title/FixedSubscription.h"
#include "Title/DynamicSubscription.h"

using namespace std;

void InicialMenu();
void PrincipalMenu(GameLibrary & gameL);
void GamesMenu(GameLibrary & gameL);
void UsersMenu(GameLibrary & gl);
void GameOperationsMenu(GameLibrary & gl, unsigned titleID);
void UserOperationsMenu(GameLibrary & gl, string mail);
void UserGameMenu(GameLibrary & gl, User * user);

// TODO: Se houver tempo mudar input para lista de ajuda
// TODO: Date problem
// TODO: promotionDisplay and updateDisplay prblem with first line
// TODO: promotion percentagem problem
/**
*  +------------------------+
*  |                        |
*  |        HEADERs         |
*  |                        |
*  +------------------------+
*/

/**
* Writes a neat header in the console with the title centerd and a line above and below all across the screen
*
* @param	title		Title of the Header
*
* @see		centerWord			(@ConsoleFunctions)
* @see		lineAcrossConsole	(@ConsoleFunctions)
*/
void mainHeader(string title)
{
	setcolor(3);
	lineAcrossConsole('=');
	cout << endl;
	setcolor(14);
	centerWord(title);
	cout << endl;
	setcolor(3);
	lineAcrossConsole('=');
	cout << endl;
	setcolor(15);
}

//-----------------------------------------------------------------------------------------------------------------------//

/**
* Writes a neat subHeader in the console with the title and a line of '-' above and below all across the screen
*
* @param	header		Title of the subHeader
*
* @see		lineAcrossConsole	(@ConsoleFunctions)
*/
void header(const string &header)
{
	cout << endl;
	setcolor(3);
	lineAcrossConsole('-');
	setcolor(14);
	cout << " " << header;
	cout << endl;
	setcolor(3);
	lineAcrossConsole('-');
	cout << endl;
	setcolor(15);
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |        DISPLAY         |
*  |                        |
*  +------------------------+
*/

void userShortDisplay(const User * user) {
	cout << " User ID:\t" << user->getUserID() << endl;
	cout << " Name:\t\t" << user->getName() << endl;
	cout << " E-Mail:\t\t" << user->getEmail() << endl;
	cout << " Address:\t" << user->getAddress() << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void promotionDisplay(string firstLine, const Sale & sale) {
	cout << firstLine << endl;
	cout << "  - Begin Date:\t" << sale.getStartDate() << endl;
	cout << "  - End Date:\t" << sale.getEndDate() << endl;
	cout << "  - Promotion:\t" << sale.getSaleFactor() * 100 << "%" << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void updateDisplay(string firstLine, const Update & update) {
	cout << firstLine << endl;
	cout << "  - Update Version:\t" << update.getVersion() << endl;
	cout << "  - Description:\t" << update.getDescription() << endl;
	cout << "  - Update Price:\t" << update.getUpdatePrice() << endl;
	cout << "  - Update Date:\t" << update.getDate() << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void sessionDisplay(string firstLine, const Session & sess) {
	cout << firstLine << endl;
	cout << "  - Date:\t\t" << sess.getDate() << endl;
	cout << "  - Duration:\t" << sess.getSessionDuration() << endl << endl;
}


//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |        SUMMARY         |
*  |                        |
*  +------------------------+
*/

void titleSummary(const set<Title*, ComparePtr<Title>> & games) {
	string type = "Online";
	for (auto & title : games)
	{
		try
		{
			title->getSubscription();
		}
		catch (NotOnlineTitle)
		{
			type = "Home";
		}
		cout << " Title ID:\t" << title->getTitleID() << endl;
		cout << " Game:\t\t" << title->getName() << endl;
		cout << " Price:\t\t" << title->getBasePrice() << endl;
		cout << " Type:\t\t" << type << endl;
		cout << " Platform:\t" << title->getPlatformName() << endl << endl;
		type = "Online";
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void promotionSummary(Title*  game) {
	vector<Sale> prov = game->getSaleHistory();
	unsigned int i = 1;
	for (auto & sale : prov)
	{
		promotionDisplay(" Sale " + i + ':', sale);
		i++;
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void updateSummary(Title*  game) {
	vector<Update> prov = game->getUpdates();
	unsigned int i = 1;
	for (auto & update : prov)
	{
		updateDisplay(" Update " + i + ':', update);
		i++;
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void usersSummary(GameLibrary & gameL) {
	map<User*, set<Title*, ComparePtr<Title>>, ComparePtr<User>> prov = gameL.getUsers();
	for (auto & user : prov)
	{
		userShortDisplay(user.first);
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void friendsSummary(const set<User*, ComparePtr<User>> & friends) {
	unsigned int i = 1;
	for (auto & fr : friends)
	{
		cout << " Friend " << i << ":\n";
		userShortDisplay(fr);
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void creditCardSummary(const vector<CreditCard> & creditCards) {
	unsigned int i = 1;
	for (auto & credit : creditCards)
	{
		cout << " Credit Card " << i << ":\n";
		cout << "  - Holder:\t\t" << credit.getHolder() << endl;
		cout << "  - Number:\t\t" << credit.getNumber() << endl;
		cout << "  - Expires On:\t" << credit.getExpiryDate() << endl;
		cout << "  - Balance:\t\t" << credit.getBalance() << endl << endl;
		i++;
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void transactionsSummary(User*  user) {
	vector<Transaction> prov = user->getTransactions();
	unsigned int i = 1;
	for (auto & trans : prov)
	{
		cout << " Transaction  " << i << ":\n";
		cout << "  - Date:\t" << trans.getDate() << endl;
		cout << "  - Value:\t" << trans.getValue() << endl;
		cout << "  - Type:\t";
		if (trans.getType() == gamePurchase) cout << "Purchased a Title";
		else if (trans.getType() == homeUpdate) cout << "Updated a Home Title";
		else if (trans.getType() == onlineSubscription) cout << "Payed an Online Title";
		cout << endl << endl;
		i++;
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void otherStatsSummary(GameLibrary & gl, User*  user) {
	cout << " Online Titles Play Time:\t" << gl.onlineTitlesPlayTime(user) << endl;
	cout << " Entire Library Cost:\t\t" << gl.userLibraryCost(user) << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void averageStatsSummary(GameLibrary & gl) {
	cout << " Average User Library Cost:\t" << gl.averageUserLibraryCost() << endl;
	cout << " Average User Library Size:\t" << gl.averageUserTitles() << endl << endl;

}

//-----------------------------------------------------------------------------------------------------------------------//

void LastNSessionsSummary(GameLibrary & gl, User * user, unsigned titleID) {
	unsigned n = intInput(" Maximum Number of Sessions: ");
	vector<Session> prov = gl.getTitle(titleID)->getLastNUserSessions(user, n);
	unsigned int i = 1;
	string title;
	for (auto & sess: prov)
	{
		title = " Session " + i + ':';
		sessionDisplay(title, sess);
		i++;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void UserSessionSummary(const map<User*, const vector<Session>*, ComparePtr<User>> & prov) {
	string title;
	for (const auto & user : prov)
	{
		cout << " User " << user.first->getUserID() << " :\n\n";
		for (size_t i = 0; i < user.second->size(); i++)
		{
			title = " Session " + i + ':';
			sessionDisplay(title, user.second->at(i));
		}
		cout << endl;
		setcolor(3);
		lineAcrossConsole('-');
		cout << endl;
		setcolor(15);
	}

}

//-----------------------------------------------------------------------------------------------------------------------//

void UserSessionSummary2(const map<User*, vector<Session>, ComparePtr<User>> * prov) {
	string title;
	for (const auto & user : *prov)
	{
		cout << " User " << user.first->getUserID() << " :\n\n";
		for (size_t i = 0; i < user.second.size(); i++)
		{
			title = " Session " + i + ':';
			sessionDisplay(title, user.second.at(i));
		}
		cout << endl;
		setcolor(3);
		lineAcrossConsole('-');
		cout << endl;
		setcolor(15);
	}

}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |     DETAILED INFO      |
*  |                        |
*  +------------------------+
*/

void titleInfo(Title * game, bool isOnline)
{
	Date d = Date::getCurrentDate();
	cout << " Title ID:\t" << game->getTitleID() << endl;
	cout << " Game:\t\t" << game->getName() << endl;
	cout << " Price:\t\t" << game->getBasePrice() << endl;
	cout << " Current Price:\t" << game->getCurrentPrice(d) << endl;
	if (isOnline) {
		cout << " Subscription:\n";
		cout << "  - Type:\t";
		if (game->getSubscription()->isFixedSubscription()) cout << "Fixed\n";
		else cout << "Dynamic\n";
		cout << "  - Price:\t" << game->getSubscription()->getSubscriptionPrice() << endl;
	}
	else
	{
		cout << " Last Update:\n";
		cout << "  - Version:\t\t" << game->getCurrentVersion().getVersion() << endl;
		cout << "  - Description:\t" << game->getCurrentVersion().getDescription() << endl;
		cout << "  - Price:\t\t" << game->getCurrentVersion().getUpdatePrice() << endl;
		cout << "  - Date:\t\t" << game->getCurrentVersion().getDate() << endl << endl;
	}
	cout << " Release Date:\t" << game->getReleaseDate() << endl;
	cout << " Age Range:\t" << game->getAgeRange().minAge << " - " << game->getAgeRange().maxAge << endl;
	cout << " Platform:\t" << game->getPlatformName() << endl;
	cout << " Genre:\t\t" << game->getGenreName() << endl;
	cout << " Company:\t" << game->getCompany() << endl;
	cout << " Users Numbe:\t" << game->getNumberUsers() << endl;
	if (isOnline) cout << " Hours Played:\t" << game->getStats() << endl;
	cout << " Last Schedule Sale:\n";
	try
	{
		cout << "  - Begin Date:\t" << game->getLastSale().getStartDate() << endl;
		cout << "  - End Date:\t" << game->getLastSale().getEndDate() << endl;
		cout << "  - Promotion:\t" << game->getLastSale().getSaleFactor() * 100 << "%" << endl << endl;
	}
	catch (InexistentSale & e)
	{
		cout << "  - " << e.getMessage() << endl << endl;
	}

	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void userInfo(User * user)
{	
	cout << " User ID:\t\t" << user->getUserID() << endl;
	cout << " Name:\t\t\t" << user->getName() << endl;
	cout << " Age:\t\t\t" << user->getAge() << endl;
	cout << " Email:			\t\t\t" << user->getEmail() << endl;
	cout << " Creation Since:\t" << user->getCreationDate() << endl;
	cout << " Adress:\n" << user->getAddress() << endl;
	cout << " # Credit Cards:\t" << user->getCreditCards().size() << endl;
	cout << " # Friends:\t\t\t" << user->getFriendsList().size() << endl;
	cout << " # Titles:\t\t\t" << user->getPurchasedGames()->size() << endl;
	cout << " # Transactions:\t" << user->getTransactions().size() << endl;
	cout << " Money Spend:\t\t" << user->getTotalTransactionsValue();
	cout << " Favorite Platform:" << user->getFavoritePlatform();
	cout << " Platforms:\n";
	set<string> plat = user->getPlatforms();
	for (auto & p : plat)
		cout << "  - " << p;

	system("pause");
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |     Add Game Help      |
*  |                        |
*  +------------------------+
*/

bool menuOnlineHome() {
	int option_number;

	cout << " Do you want to create one :" << endl << endl;

	cout << "   1 - Home Title" << endl;

	cout << "   2 - Online Title" << endl << endl;

	option_number = menuInput(" Option ? ", 1, 2);

	switch (option_number)
	{
	case 1:
		return false;
	case 2:
		return true;
	default:
		throw invalid_argument(" Error in menuOnlineHome() ");
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

gameLibraryPlatform menuPlatform() {
	int option_number;

	cout << " Platform :" << endl << endl;

	cout << "   1 - Nintendo DS" << endl;

	cout << "   2 - PC" << endl;

	cout << "   3 - PS3" << endl;

	cout << "   4 - PS4" << endl;

	cout << "   5 - Nintendo Switch" << endl;

	cout << "   6 - WII" << endl;

	cout << "   7 - XBOX 360" << endl;

	cout << "   8 - XBOX ONE" << endl;

	cout << "   0 - All the Plataforms" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 8);

	return static_cast<gameLibraryPlatform>(option_number);
}

//-----------------------------------------------------------------------------------------------------------------------//

gameLibraryGenre menuGenre(bool rank) {
	int option_number;

	cout << " Genre :" << endl << endl;

	cout << "   1 - Action" << endl;

	cout << "   2 - Adventure" << endl;

	cout << "   3 - Puzzle" << endl;

	cout << "   4 - Shooter" << endl;

	cout << "   5 - Simulation" << endl;

	cout << "   6 - RPG" << endl;

	cout << "   7 - Platformer" << endl;

	cout << "   8 - Strategy" << endl;

	cout << "   9 - Sports" << endl;

	cout << "   10 - MMO" << endl;

	if (rank) cout << "   0 - All" << endl;
	cout << endl;
	if (rank) option_number = menuInput(" Option ? ", 0, 10);
	else option_number = menuInput(" Option ? ", 1, 10);

	return static_cast<gameLibraryGenre>(option_number);
}

//-----------------------------------------------------------------------------------------------------------------------//

bool menuSubcription() {
	int option_number;

	cout << " Subscrition type (fixed or dynamic) :" << endl << endl;

	cout << "   1 - Dynamic Subscription" << endl;

	cout << "   2 - Fixed Subscription" << endl << endl;

	option_number = menuInput(" Option ? ", 1, 2);

	switch (option_number)
	{
	case 1:
		return false;
	case 2:
		return true;
	default:
		throw invalid_argument(" Error in menuSubcription() ");
	}
	//cout << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

ConsumingHabitsFilter menuTransactionsTypes() {
	int option_number;

	cout << " Consuming Habit Filter:" << endl << endl;

	cout << "   1 - Purchases" << endl;

	cout << "   2 - Updates" << endl;

	cout << "   3 - Subscriptions" << endl;

	cout << "   4 - Purchases and Updates" << endl;

	cout << "   5 - Purchases and Subscriptions" << endl;

	cout << "   6 - Updates and Subscriptions" << endl;

	cout << "   0 - All" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 6);

	return static_cast<ConsumingHabitsFilter> (option_number);
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |          ADDS          |
*  |                        |
*  +------------------------+
*/

void addGames(GameLibrary & gL)
{
	bool isOnline = menuOnlineHome();
	string name = nameNumbersInput(" Game name (only letters, space and numbers): ");
	// TODO: Verify this input control
	double price = duobleInput(" Game price: ");
	ageRange ar = ageRangeInput(" Age Range:");
	Date releaseDate = dateInput(" Release date: ");
	gameLibraryPlatform platform = menuPlatform();
	gameLibraryGenre genre = menuGenre(false);
	string company = namesInput(" Publisher name (only letters and space): ");;

	//Title(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);
	if (!isOnline) {
		if (platform != all_platforms) {
			gL.addTitle(new HomeTitle(name, price, releaseDate, ar, platform, genre, company));
			return;
		}
		else
		{
			for (int plat = nds; plat != last; plat++)
			{
				gL.addTitle(new HomeTitle(name, price, releaseDate, ar, static_cast<gameLibraryPlatform>(plat), genre, company));
			}
			return;
		}
	}
	else {
		bool isFixed = menuSubcription();
		double subsPrice = duobleInput(" Subscription price: ");

		if (isFixed) {
			if (platform != all_platforms) {
				gL.addTitle(new OnlineTitle(name, price, releaseDate, ar, platform, genre, company, new FixedSubscription(subsPrice)));
				return;
			}
			else
			{
				for (int plat = nds; plat != last; plat++)
				{
					gL.addTitle(new OnlineTitle(name, price, releaseDate, ar, static_cast<gameLibraryPlatform>(plat), genre, company, new FixedSubscription(subsPrice)));
				}
				return;
			}
		}
		else {
			if (platform != all_platforms) {
				gL.addTitle(new OnlineTitle(name, price, releaseDate, ar, platform, genre, company, new DynamicSubscription(subsPrice)));
				return;
			}
			else
			{
				for (int plat = nds; plat != last; plat++)
				{
					gL.addTitle(new OnlineTitle(name, price, releaseDate, ar, static_cast<gameLibraryPlatform>(plat), genre, company, new DynamicSubscription(subsPrice)));
				}
				return;
			}
		}
	}

}

//-----------------------------------------------------------------------------------------------------------------------//

void addUser(GameLibrary & gl) {
	string name = namesInput(" Name (only letters and space): ");
	string email = emailInput(" Email: ");
	while (email.at(0) == '<' && email.size() == 1)
	{
		email = emailInput(" Email: ");
	}
	int age = intInput(" Age: ");
	cout << " Address:\n";
	unsigned int houseNumber = intInput("   - House Number: ");
	string streetName = namesInput("   - Street Name: ");
	string city = namesInput("   - City Name: ");
	string country = namesInput("   - Country Name: ");
	Address address(houseNumber, streetName, city, country);
	try
	{
		gl.addUser(name, email, age, address);
	}
	catch (DuplicatedUser & e)
	{
		cout << endl << "  - There is already a user with this email: " << e.getEmail() << endl;
		cout << "  - Please consider taking a look at the Users Summary Menu\n\n";
		return;
	}
	cout << "\n User Added Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addSale(Title*  game) {
	Date beginDate = dateInput(" Begin date: ");
	Date endDate = dateInput(" End date: ");
	double saleFactor = menuInput(" Sale Factor (from 0 to 100): ", 0, 100) / 100;
	try
	{
		Sale sale = Sale(beginDate, endDate, saleFactor);
		game->addPromotion(sale);
	}
	catch (ExpiredSale & e)
	{
		cout << "  - " << e.getMessage() << endl << endl;
		return;
	}
	catch (OverlappingSales & e)
	{
		cout << "  - " << e.getMessage() << endl << endl;
		return;
	}
	cout << "\n Sale Added Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addUpdate(Title * game) {
	double version = duobleInput(" Update Version: ");
	string description = nameNumbersInput(" Description: ");
	double price = duobleInput(" Update Price: ");
	Date date = dateInput(" Update Date: ");
	try
	{
		game->updateTitle(new Update(date, description, version, price));
	}
	catch (OldUpdate & e)
	{
		cout << "  - " << e.getMessage() << endl << endl;
		cout << "  - Please consider taking a look at the Updates Summary Menu\n\n";
		return;
	}
	cout << "\n Update Added Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addCreditCard(User*  user) {
	string number = nameNumbersInput(" Credit Card Number: ");
	string holder = namesInput(" Credit Card Holder: ");
	Date expiryDate = dateInput(" Expiration Date: ");
	double balance = duobleInput(" Balance: ");
	CreditCard c(number, holder, expiryDate, balance);
	if (user->addCreditCard(c)) {
		cout << "\n Credit Card Added Successfully";
		return;
	}
	cout << "\n Already Exists Credit Card with that Number";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addFunds(User*  user, string creditCardNumber) {
	double funds = duobleInput(" Amout to be added: ");
	if (funds < 0)
	{
		cout << " Must be a positive number\n";
		funds = duobleInput(" Amout to be added: ");
	}
	cout << "\n Funds Successfully Added\n";
	cout << " New Balance: " << user->getCreditCard(creditCardNumber)->addFunds(funds) << endl;	
}

//-----------------------------------------------------------------------------------------------------------------------//

void addFriend(GameLibrary & gl, User * user) {
	string mail = emailInput(" Friend Email: ");
	User * frd = gl.getUser(mail);
	if (nullptr == frd) {
		cout << "\n User with that email does not exist";
		return;
	}
	else if (user->addFriend(frd))
	{
		cout << "\n Friend Successfully Added\n";
		return;
	}
	cout << "\n You already have this user as a friend:\n";
	userShortDisplay(frd);
	system("pause");
}


//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |        REMOVE          |
*  |                        |
*  +------------------------+
*/

void removeGame(GameLibrary & gL) {
	if (gL.getTitles().empty())
	{
		cout << " There are no games to remove\n";
		return;
	}
	int nameErrors = 0;
	unsigned int titleID = intInput(" Title ID Number (0 to go back): ");
	while (titleID != 0) {
		if (!gL.removeTitle(titleID))
		{
			nameErrors++;
			cout << " Inexistent title ID\n";
			if (nameErrors > 3)
			{
				cout << " You've seem to be struggling. Plz consider taking a look at the Game Summary\n";
			}
			titleID = intInput(" Title ID Number (0 to go back): ");
		}
		else
		{
			cout << "\n Title Removed Successfully";
			break;
		}
	}

}

//-----------------------------------------------------------------------------------------------------------------------//

void removeUser(GameLibrary & gL) {
	User * us;
	if (gL.getUsers().empty())
	{
		cout << " There are no games to remove\n";
		return;
	}
	int nameErrors = 0;
	string mail = emailInput(" User Email (< to go back): ");
	while (mail.at(0) != '<') {
		us = gL.getUser(mail);
		if (!gL.removeUser(us))
		{
			nameErrors++;
			cout << " Inexistent User Email\n";
			if (nameErrors > 3)
			{
				cout << " You've seem to be struggling. Plz consider taking a look at the Users Summary\n";
			}
			mail = emailInput(" User Email (< to go back): ");
		}
		else
		{
			cout << "\n User Removed Successfully";
			break;
		}
	}

}

//-----------------------------------------------------------------------------------------------------------------------//

void removeSale(Title*  game) {
	if (game->getSaleHistory().size() == 0)
	{
		cout << " There are no sales to be removed\n";
		return;
	}
	Date beginDate = dateInput(" Begin date of the Sale to be Removed: ");
	try
	{
		game->removePromotion(beginDate);
	}
	catch (SaleStarted & e)
	{
		cout << "  - " << e.getMessage() << endl << endl;
		return;
	}
	catch (InexistentSale & e)
	{
		cout << "  - " << e.getMessage() << endl;
		cout << "  - Please consider taking a look at the Sales Summary Menu\n\n";
		return;
	}
	cout << "\n Sale Removed Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//

void removeFriend(GameLibrary & gl, User*  user) {
	string mail = emailInput(" Friend Email: ");
	User * frd = gl.getUser(mail);
	if (nullptr == frd) {
		cout << "\n User with that email does not exist";
		return;
	}
	else if (user->removeFriend(frd))
	{
		cout << "\n Friend Removed Successfully"; 
		return;
	}
	cout << "\n You don't have that user as a friend";	
}

//-----------------------------------------------------------------------------------------------------------------------//

void removeCreditCard(User*  user) {
	if (user->getCreditCards().size() == 0)
	{
		cout << " There are no Credit Cards to be removed\n";
		return;
	}
	string number = nameNumbersInput(" Credit Card Number: ");
	if (user->removeCreditCard(number))
	{
		cout << "\n Credit Card Removed Successfully";
		return;
	}
	cout << "\n There is no Credit Card with that number\n";
	cout << " Please consider taking a look at the Credit Cards Summary";	
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |        RANKINGS        |
*  |                        |
*  +------------------------+
*/

void UserMostPlayedTitlesRanking(GameLibrary & gl, User * user) {
	gameLibraryPlatform platform = menuPlatform();
	gameLibraryGenre genre = menuGenre(true);
	gl.buildUserMostPlayedTitlesRanking(cout, user, platform, genre);
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void UserConsumingHabits(GameLibrary & gl, User * user) {
	ConsumingHabitsFilter filter = menuTransactionsTypes();
	gl.buildUserConsumingHabitsList(user, cout, filter);
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void globalPopRanking(GameLibrary & gl) {
	gameLibraryPlatform platform = menuPlatform();
	gameLibraryGenre genre = menuGenre(true);
	ageRange ageR = ageRangeInput( " Age Restrition:\n");
	gl.buildGlobalPopularityRanking(cout, platform, genre, ageR);
	system("pause");
}


void globalRevRanking(GameLibrary & gl) {
	gameLibraryPlatform platform = menuPlatform();
	gameLibraryGenre genre = menuGenre(true);
	ageRange ageR = ageRangeInput(" Age Restrition:\n");
	gl.buildGlobalRevenueRanking(cout, platform, genre, ageR);
	system("pause");
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |   TITLE OPERTATIONS    |
*  |                        |
*  +------------------------+
*/

void UpdateTitle(User * user, unsigned titleID) {
	if (user->updateTitle(titleID))
		cout << "\n Title Updated Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//
// TODO: Make animation if we have time
void PlayTitle(GameLibrary & gl, User * user, unsigned titleID) {
	double duration = duobleInput(" Play for (in hours): ");
	if(user->playGame(gl.getTitle(titleID), duration))
		cout << "\n Oooh... That was fun wasn't it?? You should come more often";
}

//-----------------------------------------------------------------------------------------------------------------------//

void BuyTitle(User * user, unsigned titleID) {
	if (user->buyTitle(titleID))
		cout << "\n Title Successfully Bought";
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |        INPUTS          |
*  |                        |
*  +------------------------+
*/

unsigned gameIDinput(GameLibrary & gL) {
	if (gL.getTitles().empty())
	{
		cout << " There are no games in the library\n";
		return 0;
	}
	else {
		int nameErrors = 0;
		unsigned titleID = intInput(" Title ID Number (0 to go back): ");
		while (titleID != 0) {
			if (gL.getTitle(titleID) == nullptr)
			{
				nameErrors++;
				cout << " Inexistent title ID\n";
				if (nameErrors > 3)
				{
					cout << " You've seem to be struggling. Plz consider taking a look at the Game Summary\n";
				}
				titleID = intInput(" Title ID Number (0 to go back): ");
			}
			else
			{
				return titleID;
			}
		}
		return titleID;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

unsigned userGameIDinput(User * user, bool hasToBeHome, bool hasToBeOnline, GameLibrary & gl) {
	if (hasToBeHome && hasToBeOnline)
	{
		cout << " Error in (" << __func__ << ") function parameters \n";
		return 0;
	}
	if (user->getPurchasedGames()->empty())
	{
		cout << " User has no titles in his library\n";
		return 0;
	}
	else {
		int nameErrors = 0;
		unsigned titleID = intInput(" Title ID Number (0 to go back): ");
		while (titleID != 0) {
			if (!user->hasTitle(titleID))
			{
				nameErrors++;
				cout << " User doesn't have a title with that ID\n";
				if (nameErrors > 3)
				{
					cout << " You've seem to be struggling. Plz consider taking a look at the Users Titles Summary\n";
				}
				titleID = intInput(" Title ID Number (0 to go back): ");
			}
			else if (hasToBeHome && gl.isOnlineTitle(gl.getTitle(titleID)))
			{
				cout << " Title has to be Home\n";
				nameErrors++;
				titleID = 0;
			}
			else if (hasToBeOnline && !gl.isOnlineTitle(gl.getTitle(titleID)))
			{
				cout << " Title has to be Online\n";
				nameErrors++;
				titleID = 0;
			}
			else
			{
				return titleID;
			}
		}
		return titleID;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

string userMailInput(GameLibrary & gL) {
	if (gL.getTitles().empty())
	{
		cout << " There are no users in the library\n";
		return "<";
	}
	else {
		int nameErrors = 0;
		string mail = emailInput(" User Email (< to go back): ");
		while (mail.at(0) != '<') {
			if (gL.getUser(mail) == nullptr)
			{
				nameErrors++;
				cout << " Inexistent user mail\n";
				if (nameErrors > 3)
				{
					cout << " You've seem to be struggling. Plz consider taking a look at the Users Summary\n";
				}
				mail = emailInput(" User Email (< to go back): ");
			}
			else
			{
				return mail;
			}
		}
		return mail;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

string creditCardInput(User * user) {
	if (user->getCreditCards().size())
	{
		cout << " The user does not have any Credit Card\n Please Consider Adding one first\n";
		return "<";
	}
	else {
		int nameErrors = 0;
		string number = nameNumbersInput(" Credit Card Number (< to go back): ");
		while (!(number.at(0) == '<' && number.size() == 1)) {
			if (user->getCreditCard(number) == nullptr)
			{
				nameErrors++;
				cout << " Inexistent Credit Card\n";
				if (nameErrors > 3)
				{
					cout << " You've seem to be struggling. Plz consider taking a look at the Credit Cards Summary\n";
				}
				number = nameNumbersInput(" Credit Card Number (< to go back): ");
			}
			else
			{
				return number;
			}
		}
		return number;
	}
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |          MENUS         |
*  |                        |
*  +------------------------+
*/

void PromotionMenu(GameLibrary & gl, Title * game) {
	int option_number;
	
	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Promotions Summary" << endl;

	cout << "   2 - Add Promotion" << endl;

	cout << "   3 - Remove Promotion" << endl;

	cout << "   4 - Current Promotion" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Promotions Summary");
		promotionSummary(game);
		cout << endl << endl;
		PromotionMenu(gl, game);
		break;

	case 2:
		header("Add Sale");
		addSale(game);
		cout << endl << endl;
		PromotionMenu(gl, game);
		break;
	case 3:
		header("Remove Sale");
		removeSale(game);
		cout << endl << endl;
		PromotionMenu(gl, game);
		break;
	case 4:
		header("Current Sale");
		try
		{
			Date d = Date::getCurrentDate();
			promotionDisplay(" Current Promotion:", game->getSaleOn(d));
			system("pause");
			cout << endl << endl;
		}
		catch (InexistentSale & e)
		{
			cout << "  - " << e.getMessage() << endl;
			cout << "  - Please consider taking a look at the Sales Summary Menu\n\n";
		}
		PromotionMenu(gl, game);
		break;
	case 0:
		GameOperationsMenu(gl, game->getTitleID());
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void SessionsMenu(GameLibrary & gl, Title * game) {
	int option_number;
	unsigned n;

	cout << " List:" << endl << endl;

	cout << "   1 - Last N Sessions of Each User" << endl;

	cout << "   2 - Top 3 Players Sessions" << endl;

	cout << "   3 - All Sessions (by User ID)" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("Last N Sessions of Each User");
		n = intInput(" Maximum Number of Sessions for Each User: ");
		UserSessionSummary2(&(game->getAllUsersLastNSessions(n)));
		system("pause");
		cout << endl << endl;
		SessionsMenu(gl, game);
		break;

	case 2:
		header("Top 3 Player Sessions");
		UserSessionSummary(game->getTop3PlayersSessions());
		system("pause");
		cout << endl << endl;
		SessionsMenu(gl, game);
		break;
	case 3:
		header("All Sessions by User ID");
		UserSessionSummary2(game->getTitleSessions());
		system("pause");
		cout << endl << endl;
		SessionsMenu(gl, game);
		break;
	case 0:
		GameOperationsMenu(gl, game->getTitleID());
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void UpdateMenu(GameLibrary & gl, Title * game) {
	int option_number;
	//game->updateTitle();
	//game->getUpdates();
	//gl.updateTitle

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Updates Summary" << endl;

	cout << "   2 - Last Update" << endl;

	cout << "   3 - New Update" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 2);

	switch (option_number)
	{
	case 1:
		header("Updates Summary");
		updateSummary(game);
		cout << endl << endl;
		UpdateMenu(gl, game);
		break;

	case 2:
		header("Last Update");
		updateDisplay(" Last Update:", game->getCurrentVersion());
		system("pause");
		cout << endl << endl;
		UpdateMenu(gl, game);
		break;
	case 3:
		header("Add Update");
		addUpdate(game);
		cout << endl << endl;
		UpdateMenu(gl, game);
		break;
	case 0:
		GameOperationsMenu(gl, game->getTitleID());
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void CreditCardMenu(GameLibrary & gl, User * user) {
	int option_number;
	string number;

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Credit Cards Summary" << endl;

	cout << "   2 - Add Credit Card" << endl;

	cout << "   3 - Remove Credit Card" << endl;

	cout << "   4 - Add Funds" << endl;

	cout << "   5 - Transactions" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 5);

	switch (option_number)
	{
	case 1:
		header("Credit Cards Summary");
		creditCardSummary(user->getCreditCards());
		cout << endl << endl;
		CreditCardMenu(gl, user);
		break;

	case 2:
		header("Add Credit Card");
		addCreditCard(user);
		cout << endl << endl;
		CreditCardMenu(gl, user);
		break;
	case 3:
		header("Remove Credit Card");
		removeCreditCard(user);
		cout << endl << endl;
		CreditCardMenu(gl, user);
		break;
	case 4:
		header("Add Funds");
		number = creditCardInput(user);
		if ('<' == number.at(0)) CreditCardMenu(gl, user);
		else {
			addFunds(user, number);
			cout << endl << endl;
			CreditCardMenu(gl, user);
		}
		break;
	case 5:
		header("Transactions");
		transactionsSummary(user);
		cout << endl << endl;
		CreditCardMenu(gl, user);
		break;
	case 0:
		UserOperationsMenu(gl, user->getEmail());
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void FriendsMenu(GameLibrary & gl, User * user) {
	int option_number;

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Friends Summary" << endl;

	cout << "   2 - Add Friend" << endl;

	cout << "   3 - Remove Friend" << endl;
	// TODO: Play with friend
	//cout << "   4 - Play with Friend" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("Friends Summary");
		friendsSummary(user->getFriendsList());
		cout << endl << endl;
		FriendsMenu(gl, user);
		break;

	case 2:
		header("Add Friend");
		addFriend(gl, user);
		cout << endl << endl;
		FriendsMenu(gl, user);
		break;
	case 3:
		header("Remove Sale");
		removeFriend(gl, user);
		cout << endl << endl;
		FriendsMenu(gl, user);
		break;
	case 0:
		UserOperationsMenu(gl, user->getEmail());
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void UserRankingsMenu(GameLibrary & gl, User * user) {
	int option_number;
	unsigned ID;


	cout << " Possible Lists:" << endl << endl;

	cout << "   1 - Consuming Habits" << endl;

	cout << "   2 - Most Played Titles Ranking" << endl;

	cout << "   3 - Last N Sessions" << endl;

	cout << "   4 - Other Stats" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Consuming Habits");
		UserConsumingHabits(gl, user);
		cout << endl << endl;
		UserRankingsMenu(gl, user);
		break;

	case 2:
		header("Most Played Titles Ranking");
		UserMostPlayedTitlesRanking(gl, user);
		cout << endl << endl;
		UserRankingsMenu(gl, user);
		break;
	case 3:
		header("Last N Sessions Played Online");
		ID = userGameIDinput(user, false, true, gl);
		if (0 == ID) UserRankingsMenu(gl, user);
		else {
			LastNSessionsSummary(gl, user, ID);
			system("pause");
			cout << endl << endl;
			UserRankingsMenu(gl, user);
		}
		break;
	case 4:
		header("Other Stats");
		otherStatsSummary(gl, user);
		UserRankingsMenu(gl, user);
		break;
	case 0:
		UserGameMenu(gl, user);
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void UserGameMenu(GameLibrary & gl, User * user) {
	int option_number;
	unsigned ID;

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Titles Summary" << endl;

	cout << "   2 - List and Rankings" << endl;

	cout << "   3 - Buy New Title" << endl;

	cout << "   4 - Play Title" << endl;

	cout << "   5 - Update Title" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 5);

	switch (option_number)
	{
	case 1:
		header("Titles Summary");
		titleSummary(*(user->getPurchasedGames()));
		cout << endl << endl;
		UserGameMenu(gl, user);
		break;

	case 2:
		header("Lists and Rankings");
		UserRankingsMenu(gl, user);
		break;
	case 3:
		header("Buy New Title");
		ID = gameIDinput(gl);
		if (0 == ID) UserGameMenu(gl, user);
		else {
			BuyTitle(user, ID);
			cout << endl << endl;
			UserGameMenu(gl, user);
		}
		break;
	case 4:
		header("Play Tile");
		ID = userGameIDinput(user, false, false, gl);
		if (0 == ID) UserGameMenu(gl, user);
		else {
			PlayTitle(gl, user, ID);
			cout << endl << endl;
			UserGameMenu(gl, user);
		}
		break;
	case 5:
		header("Update Tile");
		ID = userGameIDinput(user, true, false, gl);
		if (0 == ID) UserGameMenu(gl, user);
		else {
			UpdateTitle(user, ID);
			cout << endl << endl;
			UserGameMenu(gl, user);
		}
		break;
	case 0:
		UserOperationsMenu(gl, user->getEmail());
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void GameOperationsMenu(GameLibrary & gl, unsigned titleID) {
	header("Game Info");

	Title * game = gl.getTitle(titleID);
	bool isOnline = gl.isOnlineTitle(game);

	int option_number;

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Detailed Info" << endl;

	cout << "   2 - Promotions" << endl;
	
	if (isOnline) cout << "   3 - Sessions" << endl;
	else cout << "   3 - Updates" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("Detailed Information");
		titleInfo(game, isOnline);
		cout << endl << endl;
		GameOperationsMenu(gl, titleID);
		break;

	case 2:
		header("Promotions");
		PromotionMenu(gl, game);
		break;
	case 3:
		if (isOnline) {
			header("Sessions");
			SessionsMenu(gl, game);
		}
		else
		{
			header("Updates");
			UpdateMenu(gl, game);
		}
		break;
	case 0:
		GamesMenu(gl);
		break;
    default:break;
    }


}

//-----------------------------------------------------------------------------------------------------------------------//

void UserOperationsMenu(GameLibrary & gl, string mail) {
	header("User Info");

	User * user = gl.getUser(mail);

	int option_number;

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Detailed Info" << endl;

	cout << "   2 - Credit Cards" << endl;

	cout << "   3 - Friends" << endl;

	cout << "   4 - Games" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Detailed Information");
		userInfo(user);
		cout << endl << endl;
		UserOperationsMenu(gl, mail);
		break;

	case 2:
		header("Credit Cards");
		CreditCardMenu(gl, user);
		break;
	case 3:
		header("Friends");
		FriendsMenu(gl, user);
		break;
	case 4:
		header("Games");
		UserGameMenu(gl, user);
		break;
	case 0:
		UsersMenu(gl);
		break;
	default:break;
	}


}

//-----------------------------------------------------------------------------------------------------------------------//

void GamesMenu(GameLibrary & gameL) {
	header("Manage Games");
	unsigned ID;
	int option_number;

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Games Summary" << endl;

	cout << "   2 - Add Game" << endl;

	cout << "   3 - Remove Game" << endl;

	cout << "   4 - Game Info" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Games Summary");
		titleSummary(gameL.getTitles());
		cout << endl << endl;
		GamesMenu(gameL);
		break;

	case 2:
		header("Add Game");
		addGames(gameL);
		cout << endl << endl;
		GamesMenu(gameL);
		break;
	case 3:
		header("Remove Game");
		removeGame(gameL);
		cout << endl << endl;
		GamesMenu(gameL);
		break;
	case 4:
		cout << endl;
		ID = gameIDinput(gameL);
		if (0 == ID) GamesMenu(gameL);
		else GameOperationsMenu(gameL, ID);
		break;
	case 0:
		header("CREATE GAME LIBRARY");
		PrincipalMenu(gameL);
		break;
    default:break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void UsersMenu(GameLibrary & gl) {
	header("Manage Users");
	string mail;
	int option_number;

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Users Summary" << endl;

	cout << "   2 - Add User" << endl;

	cout << "   3 - Remove User" << endl;

	cout << "   4 - User Info" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Users Summary");
		usersSummary(gl);
		cout << endl << endl;
		UsersMenu(gl);
		break;

	case 2:
		header("Add User");
		addUser(gl);
		cout << endl << endl;
		UsersMenu(gl);
		break;
	case 3:
		header("Remove User");
		removeUser(gl);
		cout << endl << endl;
		UsersMenu(gl);
		break;
	case 4:
		cout << endl;
		mail = userMailInput(gl);
		if ('<' == mail.at(0)) UsersMenu(gl);
		else UserOperationsMenu(gl, mail);
		break;
	case 0:
		header("CREATE GAME LIBRARY");
		PrincipalMenu(gl);
		break;
	default:break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void ListsRankingsMenu(GameLibrary & gl) {
	header("Lists and Rankings");
	int option_number;

	cout << " Possible Rankings:" << endl << endl;

	cout << "   1 - Average Stats" << endl;

	cout << "   2 - Popularity Ranking" << endl;

	cout << "   3 - Revenue Ranking" << endl;

	// TODO: Add Online Most Played

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("Average Stats");
		averageStatsSummary(gl);
		UsersMenu(gl);
		break;

	case 2:
		header("Popularity Ranking");
		globalPopRanking(gl);
		cout << endl << endl;
		UsersMenu(gl);
		break;
	case 3:
		header("Revenue Ranking");
		globalRevRanking(gl);
		cout << endl << endl;
		UsersMenu(gl);
		break;
	case 0:
		header("CREATE GAME LIBRARY");
		PrincipalMenu(gl);
		break;
	default:break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void PrincipalMenu(GameLibrary & gameL)
{
	int option_number;

	cout << " Do you want to:" << endl << endl;

	cout << "   1 - Manage Games" << endl;

	cout << "   2 - Manage Users" << endl;

	cout << "   3 - Lists and Rankings" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		GamesMenu(gameL);
		break;
	case 2:
		UsersMenu(gameL);
		break;
	case 3:
		break;
	case 0:
		system("cls");
		mainHeader("Welcome to the Game Library");
		InicialMenu();
		break;
    default:break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void InicialMenu()
{
	GameLibrary gl = GameLibrary();

	int option_number;

	cout << " OPTIONS:" << endl << endl;

	cout << "   1 - Create Library" << endl;

	cout << "   2 - Load Library" << endl;

	cout << "   3 - Save Library" << endl;

	cout << "   0 - Exit" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("CREATE GAME LIBRARY");
		break;

	case 2:
		header("LOAD GAME LIBRARY");
		//IR para função que vai buscar o nome da pasta/ficheiro
		//gl.loadGameLibraryFromFile();
		break;
	case 3:
	    header("SAVE GAME LIBRARY");
	    cout << " Saving..." << endl;
	    gl.saveGameLibrary();
	    cout << " Done" << endl;
	    break;
	case 0:
		system("cls");
		return;
    default:break;
    }
	    PrincipalMenu(gl);
}

//=======================================================================================================================//

int main() {	
	system("title   GAME LIBRARY");
	mainHeader("Welcome to the Game Library");
	
	InicialMenu();

	return 0;
}
