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

void InicialMenu(GameLibrary & gl);
void PrincipalMenu(GameLibrary & gameL);
void GamesMenu(GameLibrary & gameL);
void UsersMenu(GameLibrary & gl);
void GameOperationsMenu(GameLibrary & gl, unsigned titleID);
void UserOperationsMenu(GameLibrary & gl, string mail);
void UserGameMenu(GameLibrary & gl, User * user);
void titleInfo(GameLibrary & gameL, Title * game, bool isOnline);

// TODO: Se houver tempo mudar input para lista de ajuda
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
	std::cout << endl;
	setcolor(14);
	centerWord(title);
	std::cout << endl;
	setcolor(3);
	lineAcrossConsole('=');
	std::cout << endl;
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
	std::cout << endl;
	setcolor(3);
	lineAcrossConsole('-');
	setcolor(14);
	std::cout << " " << header;
	std::cout << endl;
	setcolor(3);
	lineAcrossConsole('-');
	std::cout << endl;
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
	std::cout << " User ID:\t" << user->getUserID() << endl;
	std::cout << " Name:\t\t" << user->getName() << endl;
	std::cout << " E-Mail:\t" << user->getEmail() << endl;
	std::cout << " Address:\n" << user->getAddress() << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void asleepUserDisplay(string firstLine, User * user, Title* title) {
	// TODO 4: esta funcao ajuda a mostar só um user
	std::cout << firstLine << endl;
	userShortDisplay(user);
	std::cout << " Number of Searches:\t" << user->getNumberOfSearches(title) << endl;
	std::cout << " Number of Ads Seen:\t" << user->getNumberOfSeenAds(title) << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void promotionDisplay(string firstLine, const Sale & sale) {
	std::cout << firstLine << endl;
	std::cout << "  - Begin Date:\t" << sale.getStartDate() << endl;
	std::cout << "  - End Date:\t" << sale.getEndDate() << endl;
	std::cout << "  - Promotion:\t" << sale.getSaleFactor() * 100 << "%" << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void updateDisplay(string firstLine, const Update & update) {
	std::cout << firstLine << endl;
	std::cout << "  - Update Version:\t" << update.getVersion() << endl;
	std::cout << "  - Description:\t" << update.getDescription() << endl;
	std::cout << "  - Update Price:\t" << update.getUpdatePrice() << endl;
	std::cout << "  - Update Date:\t" << update.getDate() << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void sessionDisplay(string firstLine, const Session & sess) {
	std::cout << firstLine << endl;
	std::cout << "  - Date:\t\t" << sess.getDate() << endl;
	std::cout << "  - Duration:\t" << sess.getSessionDuration() << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void displayWishlist(GameLibrary& gameL, User *user) {
    priority_queue<WishlistEntry> temp = user->getWishlist();

    while(!temp.empty()) {
        titleInfo(gameL, temp.top().getTitle(), GameLibrary::isOnlineTitle(temp.top().getTitle()));
        std::cout << temp.top() << endl;
        temp.pop();
    }
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
		std::cout << " Title ID:\t" << title->getTitleID() << endl;
		std::cout << " Game:\t\t" << title->getName() << endl;
		std::cout << " Price:\t\t" << title->getBasePrice() << endl;
		std::cout << " Type:\t\t" << type << endl;
		std::cout << " Platform:\t" << title->getPlatformName() << endl << endl;
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
		promotionDisplay(" Sale " + to_string(i) + ':', sale);
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
		updateDisplay(" Update " + to_string(i) + ':', update);
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
		std::cout << endl;
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void friendsSummary(const set<User*, ComparePtr<User>> & friends) {
	unsigned int i = 1;
	for (auto & fr : friends)
	{
		std::cout << " Friend " << i << ":\n";
		userShortDisplay(fr);
		std::cout << endl;
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void creditCardSummary(const vector<CreditCard> & creditCards) {
	unsigned int i = 1;
	for (auto & credit : creditCards)
	{
		std::cout << " Credit Card " << i << ":\n";
		std::cout << "  - Holder:\t\t" << credit.getHolder() << endl;
		std::cout << "  - Number:\t\t" << credit.getNumber() << endl;
		std::cout << "  - Expires On:\t\t" << credit.getExpiryDate() << endl;
		std::cout << "  - Balance:\t\t" << credit.getBalance() << endl << endl;
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
		std::cout << " Transaction  " << i << ":\n";
		std::cout << "  - Date:\t" << trans.getDate() << endl;
		std::cout << "  - Value:\t" << trans.getValue() << endl;
		std::cout << "  - Type:\t";
		if (trans.getType() == gamePurchase) std::cout << "Purchased a Title";
		else if (trans.getType() == homeUpdate) std::cout << "Updated a Home Title";
		else if (trans.getType() == onlineSubscription) std::cout << "Played an Online Title";
		std::cout << endl << endl;
		i++;
	}
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void otherStatsSummary(GameLibrary & gl, User*  user) {
	std::cout << " Online Titles Play Time:\t" << gl.onlineTitlesPlayTime(user) << endl;
	std::cout << " Entire Library Cost:\t\t" << gl.userLibraryCost(user) << endl << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void averageStatsSummary(GameLibrary & gl) {
	if (gl.getUsers().size() == 0)
	{
		std::cout << " Average is impossible since there is no user in your Game Library\n\n";
	}
	else
	{
		std::cout << " Average User Library Cost:\t" << gl.averageUserLibraryCost() << endl;
		std::cout << " Average User Library Size:\t" << gl.averageUserTitles() << endl << endl;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void LastNSessionsSummary(GameLibrary & gl, User * user, unsigned titleID) {
	unsigned n = intInput(" Maximum Number of Sessions: ");
	vector<Session> prov = gl.getTitle(titleID)->getLastNUserSessions(user, n);
	unsigned int i = 1;
	string title;
	for (auto & sess: prov)
	{
		title = " Session " + to_string(i) + ':';
		sessionDisplay(title, sess);
		i++;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void UserSessionSummary(const map<User*, const vector<Session>*, ComparePtr<User>> & prov) {
	string title;
	for (const auto & user : prov)
	{
		std::cout << " User " << user.first->getUserID() << " :\n\n";
		for (size_t i = 0; i < user.second->size(); i++)
		{
			title = " Session " + to_string(i+1) + ':';
			sessionDisplay(title, user.second->at(i));
		}
		std::cout << endl;
		setcolor(3);
		lineAcrossConsole('-');
		std::cout << endl;
		setcolor(15);
	}

}

//-----------------------------------------------------------------------------------------------------------------------//

void UserSessionSummary2(const map<User*, vector<Session>, ComparePtr<User>> & prov) {
	string title;
	for (const auto & user : prov)
	{
		std::cout << " User " << user.first->getUserID() << " :\n\n";
		for (size_t i = 0; i < user.second.size(); i++)
		{
			title = " Session " + to_string(i+1) + ':';
			sessionDisplay(title, user.second.at(i));
		}
		std::cout << endl;
		setcolor(3);
		lineAcrossConsole('-');
		std::cout << endl;
		setcolor(15);
	}

}

//-----------------------------------------------------------------------------------------------------------------------//

void asleepUsersSummary(set<User*, CompareUsr> asleepUsers, Title * title, float minimum, UserCmpType cmd_type) {
	unsigned int i = 1;
	for (const auto & user : asleepUsers) {
		string fL = " User " + to_string(i) + ':';

		switch (cmd_type)
		{
		case ID:
			asleepUserDisplay(fL, user, title);
			break;
		case ADS:
			if (user->getNumberOfSeenAds(title) < minimum) {
				system("pause");
				return;
			}
			asleepUserDisplay(fL, user, title);
			break;
		case SEARCHES:
			if (user->getNumberOfSearches(title) < minimum) {
				system("pause");
				return;
			}
			asleepUserDisplay(fL, user, title);
			break;
		case BUYCHANCE:
			if (user->getWishlistEntry(title).getBuyChance() < minimum) {
				system("pause");
				return;
			}
			asleepUserDisplay(fL, user, title);
			break;
		default:
			break;
		}
		
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

void titleInfo(GameLibrary & gameL, Title * game, bool isOnline)
{
	Date d = GameLibrary::getLibraryDate();
	std::cout << " Title ID:\t" << game->getTitleID() << endl;
	std::cout << " Game:\t\t" << game->getName() << endl;
	std::cout << " Price:\t\t" << game->getBasePrice() << endl;
	std::cout << " Current Price:\t" << game->getCurrentPrice(d) << endl;
	if (isOnline) {
		std::cout << " Subscription:\n";
		std::cout << "  - Type:\t";
		if (game->getSubscription()->isFixedSubscription()) std::cout << "Fixed\n";
		else std::cout << "Dynamic\n";
		std::cout << "  - Price:\t" << game->getSubscription()->getSubscriptionPrice() << endl;
	}
	else
	{
		std::cout << " Last Update:\n";
		std::cout << "  - Version:\t\t" << game->getCurrentVersion().getVersion() << endl;
		std::cout << "  - Description:\t" << game->getCurrentVersion().getDescription() << endl;
		std::cout << "  - Price:\t\t" << game->getCurrentVersion().getUpdatePrice() << endl;
		std::cout << "  - Date:\t\t" << game->getCurrentVersion().getDate() << endl << endl;
	}
	std::cout << " Release Date:\t" << game->getReleaseDate() << endl;
	std::cout << " Age Range:\t" << game->getAgeRange().minAge << " - " << game->getAgeRange().maxAge << endl;
	std::cout << " Platform:\t\t" << game->getPlatformName() << endl;
	std::cout << " Genre:\t\t" << game->getGenreName() << endl;
	std::cout << " Company:\t\t" << game->getCompany() << endl;
	std::cout << " Users Number:\t" << game->getNumberUsers() << endl;
	std::cout << " Number of Searches:\t" << gameL.numberOfSearches(game) << endl;
	std::cout << " Number of Ads Seen:\t" << gameL.numberOfAdsSeen(game) << endl;
	if (isOnline) std::cout << " Hours Played:\t" << game->getStats() << endl;
	std::cout << " Last Schedule Sale:\n";
	try
	{
		std::cout << "  - Begin Date:\t" << game->getLastSale().getStartDate() << endl;
		std::cout << "  - End Date:\t" << game->getLastSale().getEndDate() << endl;
		std::cout << "  - Promotion:\t" << game->getLastSale().getSaleFactor() * 100 << "%" << endl << endl;
	}
	catch (InexistentSale & e)
	{
		std::cout << "  - " << e.getMessage() << endl << endl;
	}

	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void userInfo(User * user)
{	
	std::cout << " User ID:\t\t" << user->getUserID() << endl;
	std::cout << " Name:\t\t\t" << user->getName() << endl;
	std::cout << " Age:\t\t\t" << user->getAge() << endl;
	std::cout << " Email:\t\t\t" << user->getEmail() << endl;
	std::cout << " Creation Since:\t" << user->getCreationDate() << endl;
	std::cout << " Adress:\n" << user->getAddress() << endl;
	std::cout << " # Credit Cards:\t" << user->getCreditCards().size() << endl;
	std::cout << " # Friends:\t\t" << user->getFriendsList().size() << endl;
	std::cout << " # Titles:\t\t" << user->getPurchasedGames()->size() << endl;
	std::cout << " # Transactions:\t" << user->getTransactions().size() << endl;
	std::cout << " Money Spend:\t\t" << user->getTotalTransactionsValue() << endl;
	std::cout << " Favorite Platform:" << user->getFavoritePlatform() << endl;
	std::cout << " Platforms:\n";
	set<string> plat = user->getPlatforms();
	for (auto & p : plat)
		std::cout << "  - " << p;
	std::cout << endl;
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void companyInfo(GameLibrary &gameL)
{
	if (gameL.getCompanies().empty()) {
		std::cout << " There are no companies to show!\n";
		return;
	}

	unsigned nif = intInput(" NIF (0 to go back): ");

	Company *company = gameL.getCompany(nif);

	int nameErrors = 0;
	while (nif != 0) {
		if (company == nullptr) {
			nameErrors++;
			std::cout << " No such company found!\n";
			if (nameErrors > 3) {
				std::cout << " You seem to be struggling. Please consider taking a look at the Companies Summary\n";
			}
			nif = intInput(" NIF (0 to go back): ");
			company = gameL.getCompany(nif);
		}
		else {
			std::cout << *company << endl;

			for (Title* title : company->getTitles()) {
				titleInfo(gameL, title, GameLibrary::isOnlineTitle(title));
			}

			break;
		}
	}
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

	std::cout << " Do you want to create one :" << endl << endl;

	std::cout << "   1 - Home Title" << endl;

	std::cout << "   2 - Online Title" << endl << endl;

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

	std::cout << " Platform :" << endl << endl;

	std::cout << "   1 - Nintendo DS" << endl;

	std::cout << "   2 - PC" << endl;

	std::cout << "   3 - PS3" << endl;

	std::cout << "   4 - PS4" << endl;

	std::cout << "   5 - Nintendo Switch" << endl;

	std::cout << "   6 - WII" << endl;

	std::cout << "   7 - XBOX 360" << endl;

	std::cout << "   8 - XBOX ONE" << endl;

	std::cout << "   0 - All the Plataforms" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 8);

	return static_cast<gameLibraryPlatform>(option_number);
}

//-----------------------------------------------------------------------------------------------------------------------//

gameLibraryGenre menuGenre(bool rank) {
	int option_number;

	std::cout << " Genre :" << endl << endl;

	std::cout << "   1 - Action" << endl;

	std::cout << "   2 - Adventure" << endl;

	std::cout << "   3 - Puzzle" << endl;

	std::cout << "   4 - Shooter" << endl;

	std::cout << "   5 - Simulation" << endl;

	std::cout << "   6 - RPG" << endl;

	std::cout << "   7 - Platformer" << endl;

	std::cout << "   8 - Strategy" << endl;

	std::cout << "   9 - Sports" << endl;

	std::cout << "   10 - MMO" << endl;

	if (rank) std::cout << "   0 - All" << endl;
	std::cout << endl;
	if (rank) option_number = menuInput(" Option ? ", 0, 10);
	else option_number = menuInput(" Option ? ", 1, 10);

	return static_cast<gameLibraryGenre>(option_number);
}

//-----------------------------------------------------------------------------------------------------------------------//

bool menuSubcription() {
	int option_number;

	std::cout << " Subscription type (fixed or dynamic) :" << endl << endl;

	std::cout << "   1 - Dynamic Subscription" << endl;

	std::cout << "   2 - Fixed Subscription" << endl << endl;

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
	//std::cout << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

ConsumingHabitsFilter menuTransactionsTypes() {
	int option_number;

	std::cout << " Consuming Habits Filter:" << endl << endl;

	std::cout << "   1 - Purchases" << endl;

	std::cout << "   2 - Updates" << endl;

	std::cout << "   3 - Subscriptions" << endl;

	std::cout << "   4 - Purchases and Updates" << endl;

	std::cout << "   5 - Purchases and Subscriptions" << endl;

	std::cout << "   6 - Updates and Subscriptions" << endl;

	std::cout << "   0 - All" << endl << endl;

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

void addCompany(GameLibrary &gameL)
{
	string name = namesInput(" Name (only letters and space): ");
	unsigned nif = intInput(" NIF (only numbers): "), contact = intInput(" Contact (only numbers): ");

	gameL.addCompany(new Company(name, nif, contact));
}

//-----------------------------------------------------------------------------------------------------------------------//

void addCompany(GameLibrary &gameL, string company_name)
{
	unsigned nif = intInput(" NIF (only numbers): "), contact = intInput(" Contact (only numbers): ");

	gameL.addCompany(new Company(company_name, nif, contact));
}

//-----------------------------------------------------------------------------------------------------------------------//

void addGames(GameLibrary & gL)
{
	bool isOnline = menuOnlineHome();
	string name = nameNumbersInput(" Game name (only letters, space and numbers): ");
	double price = doubleInput(" Game price: ");
	ageRange ar = ageRangeInput(" Age Range:");
	Date releaseDate = dateInput(" Release date: ");
	gameLibraryPlatform platform = menuPlatform();
	gameLibraryGenre genre = menuGenre(false);
	string company = namesInput(" Publisher name (only letters and space): ");

	Company *comp = gL.getCompany(company);
    if (comp == nullptr) {
        std::cout << " No company named " << company << " was found in the library, please add further details below to add a new company." << endl;
        addCompany(gL, company);
    }

	//Title(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);
	if (!isOnline) {
	    Title *ht;
		if (platform != all_platforms) {
		    ht = new HomeTitle(name, price, releaseDate, ar, platform, genre, company);
			gL.addTitle(ht);
			gL.addTitleToCompany(company, ht);
			return;
		}
		else
		{
			for (int plat = nds; plat != last; plat++)
			{
			    ht = new HomeTitle(name, price, releaseDate, ar, static_cast<gameLibraryPlatform>(plat), genre, company);
				gL.addTitle(ht);
                gL.addTitleToCompany(company, ht);
			}
			return;
		}
	}
	else {
		bool isFixed = menuSubcription();
		double subsPrice = doubleInput(" Subscription price: ");

		Title *ot;
		if (isFixed) {
            auto* fs = new FixedSubscription(subsPrice);
			if (platform != all_platforms) {
			    ot = new OnlineTitle(name, price, releaseDate, ar, platform, genre, company, fs);
				gL.addTitle(ot);
				gL.addTitleToCompany(company, ot);
				return;
			}
			else
			{
				for (int plat = nds; plat != last; plat++)
				{
				    ot = new OnlineTitle(name, price, releaseDate, ar, static_cast<gameLibraryPlatform>(plat), genre, company, fs);
					gL.addTitle(ot);
					gL.addTitleToCompany(company, ot);
				}
				return;
			}
		}
		else {
		    auto* ds = new DynamicSubscription(subsPrice);
			if (platform != all_platforms) {
			    ot = new OnlineTitle(name, price, releaseDate, ar, platform, genre, company, ds);
				gL.addTitle(ot);
				gL.addTitleToCompany(company, ot);
				return;
			}
			else
			{
				for (int plat = nds; plat != last; plat++)
				{
				    ot = new OnlineTitle(name, price, releaseDate, ar, static_cast<gameLibraryPlatform>(plat), genre, company, ds);
					gL.addTitle(ot);
					gL.addTitleToCompany(company, ot);
				}
				return;
			}
		}
	}

}

//-----------------------------------------------------------------------------------------------------------------------//

void addWishlistEntry(User *user) {
    unsigned id = intInput(" Title ID (0 to go back): ");
    unsigned interest = intInput(" Enter your interest in this game (1-10) (0 to go back):" );

    if (interest > 10) interest = 10;

    Title *title = GameLibrary::getTitle(id);

    int nameErrors = 0;
    while (id != 0) {
        if (title == nullptr) {
            nameErrors++;
            std::cout << " No such game found!\n";
            if (nameErrors > 3) {
                std::cout << " You seem to be struggling. Please consider taking a look at the Games Summary\n";
            }
            id = intInput(" Title ID (0 to go back): ");
            title = GameLibrary::getTitle(id);
        }
        else {
            user->addWishlistEntry(interest, title);
            break;
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
	std::cout << " Address:\n";
	unsigned int houseNumber = intInput("   - House Number: ");
	string streetName = namesInput("   - Street Name: ");
	string city = namesInput("   - City Name: ");
	string country = namesInput("   - Country Name: ");
	Address address(houseNumber, streetName, city, country);
	try
	{
		gl.addUser(new User(name, email, age, address));
	}
	catch (DuplicatedUser & e)
	{
		std::cout << endl << "  - There is already a user with this email: " << e.getEmail() << endl;
		std::cout << "  - Please consider taking a look at the Users Summary Menu\n\n";
		return;
	}
	std::cout << "\n User Added Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addSale(Title* game) {
	Date beginDate = dateInput(" Begin date: ");
	Date endDate = dateInput(" End date: ");
	double saleFactor = static_cast<double>(menuInput(" Sale Factor (from 0 to 100): ", 0, 100)) / 100.0;
	try
	{
		Sale sale = Sale(beginDate, endDate, saleFactor);
		game->addPromotion(sale);
	}
	catch (ExpiredSale & e)
	{
		std::cout << "  - " << e.getMessage() << endl << endl;
		return;
	}
	catch (OverlappingSales & e)
	{
		std::cout << "  - " << e.getMessage() << endl << endl;
		return;
	}
	std::cout << "\n Sale Added Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addUpdate(Title * game) {
	double version = doubleInput(" Update Version: ");
	string description = nameNumbersInput(" Description: ");
	double price = doubleInput(" Update Price: ");
	Date date = dateInput(" Update Date: ");
	try
	{
		game->updateTitle(new Update(date, description, version, price));
	}
	catch (OldUpdate & e)
	{
		std::cout << "  - " << e.getMessage() << endl << endl;
		std::cout << "  - Please consider taking a look at the Updates Summary Menu\n\n";
		return;
	}
	std::cout << "\n Update Added Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addCreditCard(User*  user) {
	string number = nameNumbersInput(" Credit Card Number: ");
	string holder = namesInput(" Credit Card Holder: ");
	Date expiryDate = dateInput(" Expiration Date: ");
	double balance = doubleInput(" Balance: ");
	CreditCard c(number, holder, expiryDate, balance);
	if (user->addCreditCard(c)) {
		std::cout << "\n Credit Card Added Successfully";
		return;
	}
	std::cout << "\n Already Exists Credit Card with that Number";
}

//-----------------------------------------------------------------------------------------------------------------------//

void addFunds(User*  user, string creditCardNumber) {
	double funds = doubleInput(" Amount to be added: ");
	if (funds < 0)
	{
		std::cout << " Must be a positive number\n";
		funds = doubleInput(" Amount to be added: ");
	}
	std::cout << "\n Funds Successfully Added\n";
	std::cout << " New Balance: " << user->getCreditCard(creditCardNumber)->addFunds(funds) << endl;	
}

//-----------------------------------------------------------------------------------------------------------------------//

void addFriend(GameLibrary & gl, User * user) {
	string mail = emailInput(" Friend Email: ");
	User * frd = gl.getUser(mail);
	if (nullptr == frd) {
		std::cout << "\n User with that email does not exist";
		return;
	}
	else if (user->addFriend(frd))
	{
		std::cout << "\n Friend Successfully Added\n";
		return;
	}
	std::cout << "\n You already have this user as a friend:\n";
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
		std::cout << " There are no games to remove\n";
		return;
	}
	int nameErrors = 0;

	unsigned int titleID = intInput(" Title ID Number (0 to go back): ");

	while (titleID != 0) {

		if (!gL.removeTitle(titleID))
		{
			nameErrors++;
			std::cout << " Inexistent title ID\n";
			if (nameErrors > 3)
			{
				std::cout << " You seem to be struggling. Please consider taking a look at the Game Summary\n";
			}
			titleID = intInput(" Title ID Number (0 to go back): ");
		}
		else
		{
			std::cout << "\n Title Removed Successfully";
			break;
		}
	}

}

//-----------------------------------------------------------------------------------------------------------------------//

void removeUser(GameLibrary & gL) {
	User * us;
	if (gL.getUsers().empty())
	{
		std::cout << " There are no games to remove\n";
		return;
	}
	int nameErrors = 0;
	string mail = emailInput(" User Email (< to go back): ");
	while (mail.at(0) != '<') {
		us = gL.getUser(mail);
		if (!gL.removeUser(us))
		{
			nameErrors++;
			std::cout << " Inexistent User Email\n";
			if (nameErrors > 3)
			{
				std::cout << " You seem to be struggling. Please consider taking a look at the Users Summary\n";
			}
			mail = emailInput(" User Email (< to go back): ");
		}
		else
		{
			std::cout << "\n User Removed Successfully";
			break;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void removeWishlistEntry(User *user) {
    unsigned id = intInput(" Title ID (0 to go back): ");
    Title *title = GameLibrary::getTitle(id);

    int nameErrors = 0;
    while (id != 0) {
        if (title == nullptr) {
            nameErrors++;
            std::cout << " No such game found!\n";
            if (nameErrors > 3) {
                std::cout << " You seem to be struggling. Please consider taking a look at the Games Summary\n";
            }
            id = intInput(" Title ID (0 to go back): ");
            title = GameLibrary::getTitle(id);
        }
        else {
            user->removeWishlistEntry(title);
            break;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void removeSale(Title*  game) {
	if (game->getSaleHistory().size() == 0)
	{
		std::cout << " There are no sales to be removed\n";
		return;
	}
	Date beginDate = dateInput(" Begin date of the Sale to be Removed: ");
	try
	{
		game->removePromotion(beginDate);
	}
	catch (SaleStarted & e)
	{
		std::cout << "  - " << e.getMessage() << endl << endl;
		return;
	}
	catch (InexistentSale & e)
	{
		std::cout << "  - " << e.getMessage() << endl;
		std::cout << "  - Please consider taking a look at the Sales Summary Menu\n\n";
		return;
	}
	std::cout << "\n Sale Removed Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//

void removeFriend(GameLibrary & gl, User*  user) {
	string mail = emailInput(" Friend Email: ");
	User * frd = gl.getUser(mail);
	if (nullptr == frd) {
		std::cout << "\n User with that email does not exist";
		return;
	}
	else if (user->removeFriend(frd))
	{
		std::cout << "\n Friend Removed Successfully"; 
		return;
	}
	std::cout << "\n You don't have that user as a friend";	
}

//-----------------------------------------------------------------------------------------------------------------------//

void removeCreditCard(User*  user) {
	if (user->getCreditCards().size() == 0)
	{
		std::cout << " There are no Credit Cards to be removed\n";
		return;
	}
	string number = nameNumbersInput(" Credit Card Number: ");
	if (user->removeCreditCard(number))
	{
		std::cout << "\n Credit Card Removed Successfully";
		return;
	}
	std::cout << "\n There is no Credit Card with that number\n";
	std::cout << " Please consider taking a look at the Credit Cards Summary";	
}

//-----------------------------------------------------------------------------------------------------------------------//

void removeCompany(GameLibrary &gameL)
{
	if (gameL.getCompanies().empty()) {
		std::cout << " There are no companies to remove\n";
		return;
	}

	unsigned nif = intInput(" NIF (0 to go back): ");

	Company *company = gameL.getCompany(nif);

	int nameErrors = 0;
	while (nif != 0) {
		if (company == nullptr) {
			nameErrors++;
			std::cout << " No such company found!\n";
			if (nameErrors > 3) {
				std::cout << " You seem to be struggling. Please consider taking a look at the Companies Summary\n";
			}
			nif = intInput(" NIF (0 to go back): ");
			company = gameL.getCompany(nif);
		}
		else {
			gameL.removeCompany(company);
			std::cout << "\n Company Removed Successfully";
			break;
		}
	}
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
	gl.buildUserMostPlayedTitlesRanking(std::cout, user, platform, genre);
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void UserConsumingHabits(GameLibrary & gl, User * user) {
	ConsumingHabitsFilter filter = menuTransactionsTypes();
	gl.buildUserConsumingHabitsList(user, std::cout, filter);
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void globalPopRanking(GameLibrary & gl) {
	gameLibraryPlatform platform = menuPlatform();
	gameLibraryGenre genre = menuGenre(true);
	ageRange ageR = ageRangeInput( " Age Restriction:\n");
	gl.buildGlobalPopularityRanking(std::cout, platform, genre, ageR);
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void globalRevRanking(GameLibrary & gl) {
	gameLibraryPlatform platform = menuPlatform();
	gameLibraryGenre genre = menuGenre(true);
	ageRange ageR = ageRangeInput(" Age Restriction:\n");
	gl.buildGlobalRevenueRanking(std::cout, platform, genre, ageR);
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------//

void searchTitles(GameLibrary & gl, User * user)
{
	gameLibraryPlatform platform = menuPlatform();
	gameLibraryGenre genre = menuGenre(true);
	ageRange ageR = ageRangeInput(" Age Restriction:\n");
	std::cout << endl;
	const set<Title*, ComparePtr<Title>> & games = gl.showMatchingTitles(platform, genre, ageR);
	titleSummary(games);
	if (user != NULL) {
		for (const auto &  title : games)
			user->incNumberOfSearches(title);
	}

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
		std::cout << "\n Title Updated Successfully";
}

//-----------------------------------------------------------------------------------------------------------------------//
// TODO: Make animation if we have time
void PlayTitle(GameLibrary & gl, User * user, unsigned titleID) {
	double duration = doubleInput(" Play for (in hours): ");
	if(user->playGame(gl.getTitle(titleID), duration))
		std::cout << "\n Oooh... That was fun wasn't it?? You should come more often";
}

//-----------------------------------------------------------------------------------------------------------------------//

void BuyTitle(User * user, unsigned titleID) {
	if (user->buyTitle(titleID))
		std::cout << "\n Title Successfully Bought";
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
		std::cout << " There are no games in the library\n";
		return 0;
	}
	else {
		int nameErrors = 0;
		unsigned titleID = intInput(" Title ID Number (0 to go back): ");
		while (titleID != 0) {
			if (gL.getTitle(titleID) == nullptr)
			{
				nameErrors++;
				std::cout << " Inexistent title ID\n";
				if (nameErrors > 3)
				{
					std::cout << " You seem to be struggling. Please consider taking a look at the Game Summary\n";
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
		std::cout << " Error in (" << __func__ << ") function parameters \n";
		return 0;
	}
	if (user->getPurchasedGames()->empty())
	{
		std::cout << " User has no titles in his library\n";
		return 0;
	}
	else {
		int nameErrors = 0;
		unsigned titleID = intInput(" Title ID Number (0 to go back): ");
		while (titleID != 0) {
			if (!user->hasTitle(titleID))
			{
				nameErrors++;
				std::cout << " User doesn't have a title with that ID\n";
				if (nameErrors > 3)
				{
					std::cout << " You seem to be struggling. Please consider taking a look at the Users Titles Summary\n";
				}
				titleID = intInput(" Title ID Number (0 to go back): ");
			}
			else if (hasToBeHome && gl.isOnlineTitle(gl.getTitle(titleID)))
			{
				std::cout << " Title has to be Home\n";
				nameErrors++;
				titleID = 0;
			}
			else if (hasToBeOnline && !gl.isOnlineTitle(gl.getTitle(titleID)))
			{
				std::cout << " Title has to be Online\n";
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
	if (gL.getUsers().empty())
	{
		std::cout << " There are no users in the library\n";
		return "<";
	}
	else {
		int nameErrors = 0;
		string mail = emailInput(" User Email (< to go back): ");
		while (mail.at(0) != '<') {
			if (gL.getUser(mail) == nullptr)
			{
				nameErrors++;
				std::cout << " Inexistent user mail\n";
				if (nameErrors > 3)
				{
					std::cout << " You seem to be struggling. Please consider taking a look at the Users Summary\n";
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
	if (!user->getCreditCards().size())
	{
		std::cout << " The user does not have any Credit Card\n Please Consider Adding one first\n";
		return "<";
	}
	else {
		int nameErrors = 0;
		string number = nameNumbersInput(" Credit Card Number (< to go back): ");
		while (!(number.at(0) == '<' && number.size() == 1)) {
			if (user->getCreditCard(number) == nullptr)
			{
				nameErrors++;
				std::cout << " Inexistent Credit Card\n";
				if (nameErrors > 3)
				{
					std::cout << " You seem to be struggling. Please consider taking a look at the Credit Cards Summary\n";
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

void AsleepUsersMenu(GameLibrary & gl, Title * game) {
	int option_number;

	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - List by User ID" << endl;

	std::cout << "   2 - List by Ads Seen" << endl;

	std::cout << "   3 - List by Searches" << endl;

	std::cout << "   4 - List by Probability" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	unsigned int min;

	switch (option_number)
	{
	case 1:
		header("Potencial Buyers by ID");
		//asleepUsersSummary(set<User*, CompareUsr> asleepUsers, Title * title, float minimum, UserCmpType cmd_type)
		asleepUsersSummary(gl.OrderUsersByID(game), game, 0, ID);
		std::cout << endl << endl;
		AsleepUsersMenu(gl, game);
		break;

	case 2:
		header("Potencial Buyers by Ads Seen");
		min = intInput(" Number minimum of ads seen (0 for complete list): ");
		asleepUsersSummary(gl.OrderUsersByID(game), game, (float)min, ADS);
		std::cout << endl << endl;
		AsleepUsersMenu(gl, game);
		break;
	case 3:
		header("Potencial Buyers by Searches");
		min = intInput(" Number minimum of searches (0 for complete list): ");
		asleepUsersSummary(gl.OrderUsersByID(game), game, (float)min, SEARCHES);
		std::cout << endl << endl;
		AsleepUsersMenu(gl, game);
		break;
	case 4:
		header("Potencial Buyers by Probability");
		min = probabilityInput(" Smallest Probability (0 for complete list): ");
		asleepUsersSummary(gl.OrderUsersByID(game), game, (float)min, BUYCHANCE);
		std::cout << endl << endl;
		AsleepUsersMenu(gl, game);
		break;
	case 0:
		GameOperationsMenu(gl, game->getTitleID());
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void PromotionMenu(GameLibrary & gl, Title * game) {
	int option_number;
	
	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - Promotions Summary" << endl;

	std::cout << "   2 - Add Promotion" << endl;

	std::cout << "   3 - Remove Promotion" << endl;

	std::cout << "   4 - Current Promotion" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Promotions Summary");
		promotionSummary(game);
		std::cout << endl << endl;
		PromotionMenu(gl, game);
		break;

	case 2:
		header("Add Sale");
		addSale(game);
		std::cout << endl << endl;
		PromotionMenu(gl, game);
		break;
	case 3:
		header("Remove Sale");
		removeSale(game);
		std::cout << endl << endl;
		PromotionMenu(gl, game);
		break;
	case 4:
		header("Current Sale");
		try
		{
			Date d = GameLibrary::getLibraryDate();
			promotionDisplay(" Current Promotion:", game->getSaleOn(d));
			system("pause");
			std::cout << endl << endl;
		}
		catch (InexistentSale & e)
		{
			std::cout << "  - " << e.getMessage() << endl;
			std::cout << "  - Please consider taking a look at the Sales Summary Menu\n\n";
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

	std::cout << " List:" << endl << endl;

	std::cout << "   1 - Last N Sessions of Each User" << endl;

	std::cout << "   2 - Top 3 Players Sessions" << endl;

	std::cout << "   3 - All Sessions (by User ID)" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("Last N Sessions of Each User");
		n = intInput(" Maximum Number of Sessions for Each User: ");
		UserSessionSummary2(game->getAllUsersLastNSessions(n));
		system("pause");
		std::cout << endl << endl;
		SessionsMenu(gl, game);
		break;

	case 2:
		header("Top 3 Player Sessions");
		UserSessionSummary(game->getTop3PlayersSessions());
		system("pause");
		std::cout << endl << endl;
		SessionsMenu(gl, game);
		break;
	case 3:
		header("All Sessions by User ID");

		UserSessionSummary2(*(game->getTitleSessions()));
		system("pause");
		std::cout << endl << endl;
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

	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - Updates Summary" << endl;

	std::cout << "   2 - Last Update" << endl;

	std::cout << "   3 - New Update" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("Updates Summary");
		updateSummary(game);
		std::cout << endl << endl;
		UpdateMenu(gl, game);
		break;

	case 2:
		header("Last Update");
		updateDisplay(" Last Update:", game->getCurrentVersion());
		system("pause");
		std::cout << endl << endl;
		UpdateMenu(gl, game);
		break;
	case 3:
		header("Add Update");
		addUpdate(game);
		std::cout << endl << endl;
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

	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - Credit Cards Summary" << endl;

	std::cout << "   2 - Add Credit Card" << endl;

	std::cout << "   3 - Remove Credit Card" << endl;

	std::cout << "   4 - Add Funds" << endl;

	std::cout << "   5 - Transactions" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 5);

	switch (option_number)
	{
	case 1:
		header("Credit Cards Summary");
		creditCardSummary(user->getCreditCards());
		std::cout << endl << endl;
		CreditCardMenu(gl, user);
		break;

	case 2:
		header("Add Credit Card");
		addCreditCard(user);
		std::cout << endl << endl;
		CreditCardMenu(gl, user);
		break;
	case 3:
		header("Remove Credit Card");
		removeCreditCard(user);
		std::cout << endl << endl;
		CreditCardMenu(gl, user);
		break;
	case 4:
		header("Add Funds");
		number = creditCardInput(user);
		if ('<' == number.at(0)) CreditCardMenu(gl, user);
		else {
			addFunds(user, number);
			std::cout << endl << endl;
			CreditCardMenu(gl, user);
		}
		break;
	case 5:
		header("Transactions");
		transactionsSummary(user);
		std::cout << endl << endl;
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

	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - Friends Summary" << endl;

	std::cout << "   2 - Add Friend" << endl;

	std::cout << "   3 - Remove Friend" << endl;
	// TODO: Play with friend
	//std::cout << "   4 - Play with Friend" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("Friends Summary");
		friendsSummary(user->getFriendsList());
		std::cout << endl << endl;
		FriendsMenu(gl, user);
		break;

	case 2:
		header("Add Friend");
		addFriend(gl, user);
		std::cout << endl << endl;
		FriendsMenu(gl, user);
		break;
	case 3:
		header("Remove Sale");
		removeFriend(gl, user);
		std::cout << endl << endl;
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


	std::cout << " Possible Lists:" << endl << endl;

	std::cout << "   1 - Consuming Habits" << endl;

	std::cout << "   2 - Most Played Titles Ranking" << endl;

	std::cout << "   3 - Last N Sessions" << endl;

	std::cout << "   4 - Other Stats" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Consuming Habits");
		UserConsumingHabits(gl, user);
		std::cout << endl << endl;
		UserRankingsMenu(gl, user);
		break;

	case 2:
		header("Most Played Titles Ranking");
		UserMostPlayedTitlesRanking(gl, user);
		std::cout << endl << endl;
		UserRankingsMenu(gl, user);
		break;
	case 3:
		header("Last N Sessions Played Online");
		ID = userGameIDinput(user, false, true, gl);
		if (0 == ID) UserRankingsMenu(gl, user);
		else {
			LastNSessionsSummary(gl, user, ID);
			system("pause");
			std::cout << endl << endl;
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

void EditWishlistEntry(User * user) {
    unsigned id = intInput(" Title ID (0 to go back): ");
    unsigned interest = intInput(" Enter your interest in this game (1-10) (0 to go back):" );

    if (interest > 10) interest = 10;

    Title *title = GameLibrary::getTitle(id);

    int nameErrors = 0;
    while (id != 0) {
        if (title == nullptr) {
            nameErrors++;
            std::cout << " No such game found!\n";
            if (nameErrors > 3) {
                std::cout << " You seem to be struggling. Please consider taking a look at the Games Summary\n";
            }
            id = intInput(" Title ID (0 to go back): ");
            title = GameLibrary::getTitle(id);
        }
        else {
            user->editWishlistEntry(title, interest);
            break;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void WishlistMenu(GameLibrary & gl, User * user) {
    int option_number;

    std::cout << " Possible Actions:" << endl << endl;
    std::cout << "   1 - Wishlist Summary" << endl;
    std::cout << "   2 - Add Entry" << endl;
    std::cout << "   3 - Remove Entry" << endl;
	std::cout << "   4 - Update Entry" << endl;
	std::cout << "   5 - Show Add" << endl;
    std::cout << "   0 - Go back" << endl << endl;

    option_number = menuInput(" Option ? ", 0, 5);

    switch (option_number) {
    case 1:
        header("Wishlist Summary");
        displayWishlist(gl, user);
        WishlistMenu(gl, user);
        break;
    case 2:
        header("Add Entry");
        addWishlistEntry(user);
        WishlistMenu(gl, user);
        break;
    case 3:
        header("Remove Entry");
        removeWishlistEntry(user);
        WishlistMenu(gl, user);
        break;
    case 4:
        header("Edit Entry");
        EditWishlistEntry(user);
        WishlistMenu(gl, user);
        break;
	case 5:
	{
		header("Show Add");
		try {
			WishlistEntry entryAdd = user->nextAdvertisementTitle();
			user->incNumberOfSeenAds(entryAdd.getTitle());
			// TODO: Fazer animacao decente
			std::cout << "\tYour grandma died??\n\tDont't worry we have the perfect game to make you happier\n\t\t" << entryAdd.getTitle()->getName() << endl << endl;
		}
		catch (const NoMatchingWishlistEntryUser)
		{
			std::cout << " There is no ads to be shown\n\n";
		}
		WishlistMenu(gl, user);
		break;
	}
    case 0:
        UserOperationsMenu(gl, user->getEmail());
        break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void UserGameMenu(GameLibrary & gl, User * user) {
	int option_number;
	unsigned ID;

	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - Titles Summary" << endl;

	std::cout << "   2 - List and Rankings" << endl;

	std::cout << "   3 - Buy New Title" << endl;

	std::cout << "   4 - Play Title" << endl;

	std::cout << "   5 - Update Title" << endl;

	std::cout << "   6 - Search Game" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 6);

	switch (option_number)
	{
	case 1:
		header("Titles Summary");
		titleSummary(*(user->getPurchasedGames()));
		std::cout << endl << endl;
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
			std::cout << endl << endl;
			try
			{
				// Show add
				WishlistEntry entryAdd = user->nextAdvertisementTitle();
				user->incNumberOfSeenAds(entryAdd.getTitle());
				// TODO: Fazer animacao decente
				std::cout << "\t That game is boring af!!\n\t Have you tried the new " << entryAdd.getTitle()->getName() << "??\n\t";
				std::cout << " Studies say that it can make your reflexes 1.001 times better!!" << endl << endl;
			}
			catch (const NoMatchingWishlistEntryUser){}
			UserGameMenu(gl, user);
		}
		break;
	case 4:
		header("Play Title");
		ID = userGameIDinput(user, false, false, gl);
		if (0 == ID) UserGameMenu(gl, user);
		else {
			PlayTitle(gl, user, ID);
			std::cout << endl << endl;
			try
			{
				// Show add
				WishlistEntry entryAdd = user->nextAdvertisementTitle();
				user->incNumberOfSeenAds(entryAdd.getTitle());
				// TODO: Fazer animacao decente
				std::cout << "\t Wouldn't you prefer to be spennding your time doing something else??\n\t";
				std::cout << " Word on the street is that " << entryAdd.getTitle()->getName() << " is freaking great!!\n\t";
				Date d = GameLibrary::getLibraryDate();
				std::cout << " Buy it now for as low as " << entryAdd.getTitle()->getCurrentPrice(d) << "!!\n";
				std::cout << "\t Don't worry about the money, your mother's purse is full of it!!!" << endl << endl;
			}
			catch (const NoMatchingWishlistEntryUser) {}
			UserGameMenu(gl, user);
		}
		break;
	case 5:
		header("Update Title");
		ID = userGameIDinput(user, true, false, gl);
		if (0 == ID) UserGameMenu(gl, user);
		else {
			UpdateTitle(user, ID);
			std::cout << endl << endl;
			UserGameMenu(gl, user);
		}
		break;
	case 6:
	{
		header("Search Titles");
		searchTitles(gl, user);
		std::cout << endl << endl;
		try
		{
			// Show add
			WishlistEntry entryAdd = user->nextAdvertisementTitle();
			user->incNumberOfSeenAds(entryAdd.getTitle());
			// TODO: Fazer animacao decente
			std::cout << "\t This is not an ad, but " << entryAdd.getTitle()->getName() << " is the game of the moment\n\t";
			std::cout << " Thought you would be interested in this information..." << endl << endl;
		}
		catch (const NoMatchingWishlistEntryUser) {}
		UserGameMenu(gl, user);
		break;
	}
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

	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - Detailed Info" << endl;

	std::cout << "   2 - Promotions" << endl;
	
	if (isOnline) std::cout << "   3 - Sessions" << endl;
	else std::cout << "   3 - Updates" << endl;

	std::cout << "   4 - Potencial Buyers (asleep users)" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Detailed Information");
		titleInfo(gl, game, isOnline);
		std::cout << endl << endl;
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
	case 4:
		header("Potencial Buyers");
		// TODO 1: aqui vai ser chamado o menu AsleepUsersMenu
		std::cout << endl << endl;
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

	int option_number;

	std::cout << " Possible Actions:" << endl << endl;
	std::cout << "   1 - Detailed Info" << endl;
	std::cout << "   2 - Credit Cards" << endl;
	std::cout << "   3 - Friends" << endl;
	std::cout << "   4 - Games" << endl;
	std::cout << "   5 - Wishlist" << endl;
	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 5);

	switch (option_number)
	{
	case 1:
		header("Detailed Information");
		userInfo(user);
		std::cout << endl << endl;
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
	case 5:
	    header("Wishlist");
	    WishlistMenu(gl, user);
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

	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - Games Summary" << endl;

	std::cout << "   2 - Add Game" << endl;

	std::cout << "   3 - Remove Game" << endl;

	std::cout << "   4 - Game Info" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Games Summary");
		titleSummary(gameL.getTitles());
		std::cout << endl << endl;
		GamesMenu(gameL);
		break;

	case 2:
		header("Add Game");
		addGames(gameL);
		std::cout << endl << endl;
		GamesMenu(gameL);
		break;
	case 3:
		header("Remove Game");
		removeGame(gameL);
		std::cout << endl << endl;
		GamesMenu(gameL);
		break;
	case 4:
		std::cout << endl;
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

	std::cout << " Possible Actions:" << endl << endl;

	std::cout << "   1 - Users Summary" << endl;

	std::cout << "   2 - Add User" << endl;

	std::cout << "   3 - Remove User" << endl;

	std::cout << "   4 - User Info" << endl;

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Users Summary");
		usersSummary(gl);
		std::cout << endl << endl;
		UsersMenu(gl);
		break;

	case 2:
		header("Add User");
		addUser(gl);
		std::cout << endl << endl;
		UsersMenu(gl);
		break;
	case 3:
		header("Remove User");
		removeUser(gl);
		std::cout << endl << endl;
		UsersMenu(gl);
		break;
	case 4:
		std::cout << endl;
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

	std::cout << " Possible Rankings:" << endl << endl;

	std::cout << "   1 - Average Stats" << endl;

	std::cout << "   2 - Popularity Ranking" << endl;

	std::cout << "   3 - Revenue Ranking" << endl;

	std::cout << "   4 - Search Titles" << endl;

	// TODO: Add Online Most Played

	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Average Stats");
		averageStatsSummary(gl);
		ListsRankingsMenu(gl);
		break;

	case 2:
		header("Popularity Ranking");
		globalPopRanking(gl);
		std::cout << endl << endl;
		ListsRankingsMenu(gl);
		break;
	case 3:
		header("Revenue Ranking");
		globalRevRanking(gl);
		std::cout << endl << endl;
		ListsRankingsMenu(gl);
		break;
	case 4:
		header("Search Titles");
		searchTitles(gl, NULL);
		std::cout << endl << endl;
		ListsRankingsMenu(gl);
		break;
	case 0:
		header("CREATE GAME LIBRARY");
		PrincipalMenu(gl);
		break;
	default:break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void CompaniesMenu(GameLibrary &gameL)
{
	header("Manage Companies");

	std::cout << " Possible options:\n" << endl;
	std::cout << "   1 - Companies Summary" << endl;
	std::cout << "   2 - Add Company" << endl;
	std::cout << "   3 - Remove Company" << endl;
	std::cout << "   4 - Company Info" << endl;
	std::cout << "   0 - Go back" << endl << endl;

	int option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Companies Summary");
		for (auto it : gameL.getCompanies()) {
			std::cout << *it << endl;
		}
		std::cout << endl << endl;
		CompaniesMenu(gameL);
		break;
	case 2:
	    header("Add Company");
		addCompany(gameL);
		std::cout << endl << endl;
		CompaniesMenu(gameL);
		break;
	case 3:
	    header("Remove Company");
	    removeCompany(gameL);
	    std::cout << endl << endl;
	    CompaniesMenu(gameL);
		break;
	case 4:
	    header("Company Info");
		companyInfo(gameL);
	    std::cout << endl << endl;
	    CompaniesMenu(gameL);
		break;
	case 0:
		header("CREATE GAME LIBRARY");
		PrincipalMenu(gameL);
		break;
	default:break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

// TODO: hashtable being updated
void DateMenu(GameLibrary &gameL)
{
	header("Date");

	std::cout << " Possible options:\n" << endl;
	std::cout << "   1 - Current Date" << endl;
	std::cout << "   2 - Go to a Future Date" << endl;
	std::cout << "   3 - Move forward X days" << endl;
	std::cout << "   4 - Move forward X months" << endl;
	std::cout << "   5 - Move forward X years" << endl;
	std::cout << "   0 - Go back" << endl << endl;

	int option_number = menuInput(" Option ? ", 0, 5);

	switch (option_number)
	{
	case 1:
		header("Current Date");
		std::cout << " Present Day: " << gameL.getLibraryDate();
		std::cout << endl;
		DateMenu(gameL);
		break;
	case 2:
	{
		header("Choose Future Date");
		bool newDate = false;
		while (!newDate) {
			Date futureDate = dateInput(" Future date: ");
			try
			{
				newDate = true;
				gameL.goToDate(futureDate);
			}
			catch (const OldDate)
			{
				newDate = false;
			}
			std::cout << endl;
		}
		gameL.addSleepyUsers();
		std::cout << endl;
		DateMenu(gameL);
		break;
	}
	case 3:
		header("Move X Days Forward");
		gameL.advanceXdays(intInput(" Number of Days: "));
		gameL.addSleepyUsers();
		std::cout << endl << endl;
		DateMenu(gameL);
		break;
	case 4:
		header("Move X Months Forward");
		gameL.advanceXmonths(intInput(" Number of Months: "));
		gameL.addSleepyUsers();
		std::cout << endl << endl;
		DateMenu(gameL);
		break;
	case 5:
		header("Move X Years Forward");
		gameL.advanceXyears(intInput(" Number of Years: "));
		gameL.addSleepyUsers();
		std::cout << endl << endl;
		DateMenu(gameL);
		break;
	case 0:
		header("CREATE GAME LIBRARY");
		PrincipalMenu(gameL);
		break;
	default:break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------//

void PrincipalMenu(GameLibrary & gameL)
{
	int option_number;

	std::cout << " Do you want to:" << endl << endl;
	std::cout << "   1 - Manage Games" << endl;
	std::cout << "   2 - Manage Users" << endl;
	std::cout << "   3 - Manage Companies" << endl;
	std::cout << "   4 - Lists and Rankings" << endl;
	std::cout << "   5 - Fast Forward" << endl;
	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 5);

	switch (option_number)
	{
	case 1:
		GamesMenu(gameL);
		break;
	case 2:
		UsersMenu(gameL);
		break;
	case 3:
		CompaniesMenu(gameL);
		break;
	case 4:
		ListsRankingsMenu(gameL);
		break;
	case 5:
		DateMenu(gameL);
		break;
	case 0:
		system("cls");
		mainHeader("Welcome to the Game Library");
		InicialMenu(gameL);
		break;
    default:break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void InicialMenu(GameLibrary & gl)
{

	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - Create Library" << endl;
	std::cout << "   2 - Load Library" << endl;
	std::cout << "   3 - Save Library" << endl;
	std::cout << "   0 - Exit" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("CREATE GAME LIBRARY");
		PrincipalMenu(gl);
		break;

	case 2:
		header("LOAD GAME LIBRARY");
		//IR para função que vai buscar o nome da pasta/ficheiro
		std::cout << " Loading..." << endl;
		try {
		    gl.loadGameLibrary();

		} catch (const AlreadyLoaded &al) {
		    std::cout << al.getMessage() << endl;
		    PrincipalMenu(gl);
		    break;
		}

		std::cout << " Done" << endl;
		PrincipalMenu(gl);
		break;
	case 3:
	    header("SAVE GAME LIBRARY");
		gl.updateHashTable();
	    std::cout << " Saving..." << endl;
	    gl.saveGameLibrary();
	    std::cout << " Done" << endl << endl;
	    InicialMenu(gl);
	    break;
	case 0:
		system("cls");
		return;
    default:break;
    }
}

//=======================================================================================================================//

int main() {	
	system("title   GAME LIBRARY");
	mainHeader("Welcome to the Game Library");

	unsigned int months;
	while ((months = intInput(" Setup number of months that has to go by to a user be considered asleep: ")) == 0) {
		std::cout << endl;
	}
	GameLibrary gl = GameLibrary(months);

	std::cout << endl << endl;

	InicialMenu(gl);

	return 0;
}
