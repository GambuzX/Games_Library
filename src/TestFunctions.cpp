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
	cout << "  - Update Price:\t" << update.getuUpdatePrice() << endl;
	cout << "  - Update Date:\t" << update.getDate() << endl << endl;
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
	for (auto & title : games)
	{
		cout << " Title ID:\t" << title->getTitleID() << endl;
		cout << " Game:\t\t" << title->getName() << endl;
		cout << " Price:\t\t" << title->getBasePrice() << endl;
		cout << " Platform:\t" << title->getPlatformName() << endl << endl;
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
	for (auto & fr : friends)
	{
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
		cout << "  - Price:\t\t" << game->getCurrentVersion().getuUpdatePrice() << endl;
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
	//cout << " Credit Cards:\n";
	//creditCardSummary(user->getCreditCards());
	cout << " # Friends:\t\t\t" << user->getFriendsList().size() << endl;
	//cout << " Friends:\n";
	//friendsSummary(user->getFriendsList());
	cout << " # Titles:\t\t\t" << user->getPurchasedGames()->size() << endl;
	//cout << " Titles:\n";
	//titleSummary(*(user->getPurchasedGames()));
	cout << " # Transactions:\t" << user->getTransactions().size() << endl;
	//user->getTransactions();
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
	gameLibraryGenre genre = menuGenre();
	string company = nameInput(" Publisher name (only letters and space): ");;

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
	string name = nameInput(" Name (only letters and space): ");
	string email = emailInput(" Email: ");
	while (email.at(0) == '<' && email.size() == 1)
	{
		email = emailInput(" Email: ");
	}
	int age = intInput(" Age: ");
	cout << " Address:\n";
	unsigned int houseNumber = intInput("   - House Number: ");
	string streetName = nameInput("   - Street Name: ");
	string city = nameInput("   - City Name: ");
	string country = nameInput("   - Country Name: ");
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
	string holder = nameInput(" Credit Card Holder: ");
	Date expiryDate = dateInput(" Expiration Date: ");
	double balance = duobleInput(" Balance: ");
	CreditCard c(number, holder, expiryDate, balance);
	if (user->addCreditCard(c)) {
		cout << "\n Credit Card Added Successfully";
		return;
	}
	cout << "\n Credit Card Cannot be Added";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addFunds(User*  user) {
	string number = nameNumbersInput(" Credit Card Number: ");
	string holder = nameInput(" Credit Card Holder: ");
	Date expiryDate = dateInput(" Expiration Date: ");
	double balance = duobleInput(" Balance: ");
	CreditCard c(number, holder, expiryDate, balance);
	if (user->addCreditCard(c)) {
		cout << "\n Credit Card Added Successfully";
		return;
	}
	cout << "\n Credit Card Cannot be Added";
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

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |        SUBMENUS        |
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
	
	switch (option_number)
	{
	case 0: return all_platforms;
	case 1: return nds;
	case 2: return pc;
	case 3: return ps3;
	case 4: return ps4;
	case 5: return switche;
	case 6: return wii;
	case 7: return xbox1;
	case 8: return xbox360;
	// Should never reach here
	default:
		throw invalid_argument(" Error in menuPlatform() ");
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

gameLibraryGenre menuGenre() {
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

	cout << "   10 - MMO" << endl << endl;

	option_number = menuInput(" Option ? ", 1, 10);

	switch (option_number)
	{
	case 1:
		return action;
	case 2:
		return adventure;
	case 3:
		return puzzle;
	case 4:
		return shooter;
	case 5:
		return simulation;
	case 6:
		return rpg;
	case 7:
		return platformer;
	case 8:
		return strategy;
	case 9:
		return sports;
	case 10:
		return mmo;
	default:
		throw invalid_argument(" Error in menuGenre() ");
	}
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

//TODO: Later if we have time
void SessionsMenu(GameLibrary & gl, Title * game) {
	int option_number;
	//game->updateTitle();
	//game->getUpdates();
	//gl.updateTitle
	//game->getStats
	//game->getCurrentVersion

	cout << " List:" << endl << endl;

	cout << "   1 - Last 10 Sessions" << endl;

	cout << "   2 - Top 3 Players Sessions" << endl;

	cout << "   3 - All Sessions (by User Mail)" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		//header("Promotions Summary");
		//promotionSummary(game);
		//cout << endl << endl;
		//PromotionMenu(gl, game);
		break;

	case 2:
		//header("Add Sale");
		//addSale(game);
		//cout << endl << endl;
		//PromotionMenu(gl, game);
		break;
	case 3:
		//header("Remove Sale");
		//removeSale(game);
		//cout << endl << endl;
		//PromotionMenu(gl, game);
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

	cout << " Possible Actions:" << endl << endl;

	cout << "   1 - Credit Cards Summary" << endl;

	cout << "   2 - Add Credit Card" << endl;

	cout << "   3 - Add Funds" << endl;

	cout << "   4 - Transactions" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

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
		header("Add Funds");
		//removeSale(game);
		cout << endl << endl;
		CreditCardMenu(gl, user);
		break;
	case 4:
		header("Current Sale");
	
		CreditCardMenu(gl, user);
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
		cout << endl << endl;
		GameOperationsMenu(gl, titleID);
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
		cout << endl << endl;
		GameOperationsMenu(gl, titleID);
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

	//user->addCreditCard;
	//user->addFriend;
	//user->addTransaction;
	//user->buyTitle;
	//user->playGame;
	//user->updateTitle;

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
		//PromotionMenu(gl, game);
		cout << endl << endl;
		UserOperationsMenu(gl, mail);
		break;
	case 3:
		//header("Sessions");
		//SessionsMenu(gl, game);
		cout << endl << endl;
		UserOperationsMenu(gl, mail);
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

void PrincipalMenu(GameLibrary & gameL)
{
	int option_number;

	cout << " Do you want to:" << endl << endl;

	cout << "   1 - Manage Games" << endl;

	cout << "   2 - Manage Users" << endl;
	//TODO: Nao gosto mas é para poder ver os jogos, jogar, comprar...
	cout << "   3 - Login as a User" << endl;

	cout << "   4 - Make a List/Ranking" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		GamesMenu(gameL);
		break;
	case 2:
		UsersMenu(gameL);
		break;
	case 3:
		header("Login as User");
		break;
	case 4:
		header("Lists and Rankings");
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
