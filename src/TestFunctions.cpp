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

/**
* Writes a neat subHeader in the console with the title and a line of '-' above and below all across the screen
*
* @param	header		Title of the subHeader
*
* @see		lineAcrossConsole	(@ConsoleFunctions)
*/
void header(string header)
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
	cout << endl;
}

// TODO: Por para 2 em vez de todas??
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
	cout << endl;
}

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
	cout << endl;
}

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
	cout << endl;
}

void titleSummary(GameLibrary & gameL) {
	set<Title*, ComparePtr<Title>> prov = gameL.getTitles();
	for (auto & title: prov)
	{
		cout << " Title ID:\t" << title->getTitleID() << endl;
		cout << " Game:\t\t" << title->getName() << endl;
		cout << " Price:\t\t" << title->getBasePrice() << endl;
		cout << " Platform:\t" << title->getPlatformName() << endl << endl;
	}
	system("pause");
}

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
	if (!isOnline){
		if(platform != all_platforms){
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

void removeGame(GameLibrary & gL) {
	if (gL.getTitles().size() == 0)
	{
		cout << " There are no games to remove\n";
		return;
	}
	int nameErrors = 0;
	int titleID = intInput(" Title ID Number (0 to go back): ");
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

unsigned gameIDinput(GameLibrary & gL) {
	if (gL.getTitles().size() == 0)
	{
		cout << " There are no games in the library\n";
		return 0;
	}
	else {
		int nameErrors = 0;
		unsigned titleID = intInput(" Title ID Number (0 to go back): ");
		while (titleID != 0) {
			if (gL.getTitle(titleID) == NULL)
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

void titleInfo(GameLibrary & gl, Title * game) 
{
	cout << " Title ID:\t" << game->getTitleID() << endl;
	cout << " Game:\t\t" << game->getName() << endl;
	cout << " Price:\t\t" << game->getBasePrice() << endl;
	cout << " Current Price:\t" << game->getCurrentPrice(Date::getCurrentDate()) << endl;
	cout << " Release Date:\t" << game->getReleaseDate() << endl;
	cout << " Age Range:\t" << game->getAgeRange().minAge << " - " << game->getAgeRange().maxAge << endl;
	cout << " Platform:\t" << game->getPlatformName() << endl;
	cout << " Genre:\t\t" << game->getGenreName() << endl;
	cout << " Company:\t" << game->getCompany() << endl;
	cout << " Number of Users:\t" << game->getNumberUsers() << endl;
	cout << " Last Schedule Sale:\n";
	cout << "  - Begin Date:\t" << game->getLastSale().getStartDate() << endl;
	cout << "  - End Date:\t" << game->getLastSale().getEndDate() << endl;
	cout << "  - Promotion:\t" << game->getLastSale().getSaleFactor()*100 << "%" << endl;
	
	///////
	game->getStats();
	game->getSubscription();
	//game->getTimePlayed();
	//game->getUpdatePrice();
	game->getUpdates();

	system("pause");
}
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
		//eader("Games Summary");
		//titleSummary(gameL);
		//cout << endl << endl;
		//GamesMenu(gameL);
		break;

	case 2:
		//header("Add Game");
		//addGames(gameL);
		//cout << endl << endl;
		//GamesMenu(gameL);
		break;
	case 3:
		//header("Remove Game");
		//removeGame(gameL);
		//cout << endl << endl;
		//GamesMenu(gameL);
		break;
	case 4:
		//GameOperationsMenu(gameL);
		break;
	case 0:
		GamesMenu(gl);
		break;
	}


}

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
		titleSummary(gameL);
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
	}
}

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
		header("Manage Users");
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
	}
}

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
	}
	    PrincipalMenu(gl);
}

int main() {	
	system("title   GAME LIBRARY");
	mainHeader("Welcome to the Game Library");
	
	InicialMenu();





	return 0;
}
