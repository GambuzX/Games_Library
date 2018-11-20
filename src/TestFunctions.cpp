#include <iostream>
#include <limits>
#include "Utilities\Date.h"
#include "GameLibrary.h"
//#include "Utilities/Logger.h"
#include "Utilities\ConsoleFunctions.h"
#include "Title/HomeTitle.h"
#include "Title/OnlineTitle.h"
#include "Title/FixedSubscription.h"
#include "Title/DynamicSubscription.h"

using namespace std;
/*
Logger logger;

void handle_option1(GameLibrary &gl)
{
    string titleType;
    string name;
    double price;
    int minAge, maxAge;
    unsigned int year, month, day;
    string platform;
    string genre;
    string company;

    cout << "Insert title type (home, online): " << endl;
    cin >> titleType;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Name: "<< endl;
    getline(cin, name);

    cout << "Price: " << endl;
    cin >> price;

    cout << "Age Range (minAge, maxAge): " << endl;
    cin >> minAge >> maxAge;
    struct ageRange ar{minAge, maxAge};

    cout << "Release date (year, month, day): " << endl;
    cin >> year >> month >> day;
    Date releaseDate(day, month, year);

    cout << "Platform: " << endl;
    cin >> platform;

    cout << "Genre: " << endl;
    cin >> genre;

    cout << "Publisher: " << endl;
    cin >> company;


    //Title(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);
    if (titleType == "home")
        gl.addTitle(new HomeTitle(name, price, releaseDate, ar, platform, genre, company));
    else if (titleType == "online") {
        string subscriptionType;
        double subsPrice;

        cout << "Subscrition type (fixed, dynamic): " << endl;
        cin >> subscriptionType;

        cout << "Subscription price: " << endl;
        cin >> subsPrice;

        if (subscriptionType == "fixed") {
            gl.addTitle(new OnlineTitle(name, price, releaseDate, ar, platform, genre, company, new FixedSubscription(subsPrice)));
        } else if (subscriptionType == "online") {
            gl.addTitle(new OnlineTitle(name, price, releaseDate, ar, platform, genre, company, new DynamicSubscription(subsPrice)));
        } else {
            logger.error("InvalidOption");
        }
    }

}
*/

void FirstMenu();

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

/**
* Removes spaces:
* - Repetitive spaces in the middle of the name ;
* - From the beginning and the end.
*
* @param	name	Name that you want to remove the spaces from
*
* @return	string	String with the formatted name
*/
string removeSpace(string name) {

	int contaEspaco = 0;

	for (unsigned int i = 0; i < name.length();)
	{
		if (isblank(name[i])) {
			contaEspaco += 1;
			if (contaEspaco > 1)
			{
				name.erase(name.begin() + i);
			}
			else
			{
				i++;
			}
		}
		else
		{
			contaEspaco = 0;
			i++;
		}

	}

	if (isblank(name[0]))
	{
		name.erase(name.begin());
	}

	if (isblank(name[name.length() - 1]))
	{
		name.erase(name.end() - 1);
	}

	return name;

}


/**
* Robustness of the name Input:
* - Checks if the word has other characters than letters and spaces;
* - Remove spaces
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for the name
*
* @return	string			String with the name
*
* @see		removeSpace
* @see		getlineZ		(@		ConsoleFunctions)
*/
string nameInput(string question)
{
	bool validInput = false;
	bool ErrorFlag = false;
	bool letterFlag = false;
	string name;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!validInput)
	{
		cin.clear();
		getlineZ(cin, name);

		ErrorFlag = false;
		letterFlag = false;

		if (cin.eof())
		{
			cin.clear();
			ErrorFlag = true;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}
		else
		{
			// Search for invalid characters //
			for (size_t j = 0; j < name.size(); j++)
			{
				if ((unsigned int)name.at(j) != 32 && !isalpha((unsigned char)name.at(j)))
				{
					ErrorFlag = true;
					break;
				}
				if (isalpha((unsigned char)name.at(j)))
				{
					letterFlag = true;
				}
			}
		}
		if ("" == name || !letterFlag)
		{
			ErrorFlag = true;
		}

		validInput = !ErrorFlag;

		if (ErrorFlag)
		{
			clrscr(currentPos);
		}
	}

	return removeSpace(name);
}

/**
* Robustness of the name with Numbers Input:
* - Checks if the word has other characters than letters, spaces and numbers;
* - Remove spaces
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for the name
*
* @return	string			String with the name
*
* @see		removeSpace
* @see		getlineZ		(@		ConsoleFunctions)
*/
string nameNumbersInput(string question)
{
	bool validInput = false;
	bool ErrorFlag = false;
	bool letterFlag = false;
	string name;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!validInput)
	{
		cin.clear();
		getlineZ(cin, name);

		ErrorFlag = false;
		letterFlag = false;

		if (cin.eof())
		{
			cin.clear();
			ErrorFlag = true;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}
		else
		{
			// Search for invalid characters //
			for (size_t j = 0; j < name.size(); j++)
			{
				if ((unsigned int)name.at(j) != 32 && !isalnum((unsigned char)name.at(j)))
				{
					ErrorFlag = true;
					break;
				}
				if (isalnum((unsigned char)name.at(j)))
				{
					letterFlag = true;
				}
			}
		}
		if ("" == name || !letterFlag)
		{
			ErrorFlag = true;
		}

		validInput = !ErrorFlag;

		if (ErrorFlag)
		{
			clrscr(currentPos);
		}
	}

	return removeSpace(name);
}

/**
* Check if there is any other character than an escape line in the end of the input
*
* @param	&in		Input string stream that you want to check the end
*
* @return	bool	Boolean value correspondent to if there is something different to '\n' in the end
*/
bool afterNumber(istringstream & in)
{
	int numbers = 0;
	char ch;
	if (in.get(ch))
	{
		return true;
	}
	return false;
}

/**
* Robustness of the double Input:
* - Checks if there is something left on the istringstream after the numbers
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for a double
*
* @return	double			Double with the desired number
*
* @see		afterNumber
* @see		getlineZ		(@		ConsoleFunctions)
*/
double duobleInput(string question)
{
	double option;
	bool valid = false;

	string prov;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!valid)
	{
		getlineZ(cin, prov);
		istringstream iss(prov);
		while (!(iss >> option))
		{
			if (iss.eof())
			{
				iss.clear();
				cin.clear();
			}
			if (iss.fail())
			{
				iss.clear();
				cin.clear();
			}

			clrscr(currentPos);
			getlineZ(cin, prov);
			iss.str(prov);
		}
		if (!afterNumber(iss))
		{
			valid = true;
		}
		else
		{
			cin.clear();
		}
		if (!valid)
		{
			clrscr(currentPos);
		}
	}

	return option;
}

/**
* Robustness of the int Input:
* - Checks if there is something left on the istringstream after the numbers
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for an int
*
* @return	double			Int with the desired number
*
* @see		afterNumber
* @see		getlineZ		(@		ConsoleFunctions)
*/
int intInput(string question)
{
	int option;
	bool valid = false;

	string prov;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!valid)
	{
		getlineZ(cin, prov);
		istringstream iss(prov);
		while (!(iss >> option))
		{
			if (iss.eof())
			{
				iss.clear();
				cin.clear();
			}
			if (iss.fail())
			{
				iss.clear();
				cin.clear();
			}

			clrscr(currentPos);
			getlineZ(cin, prov);
			iss.str(prov);
		}
		if (!afterNumber(iss))
		{
			valid = true;
		}
		else
		{
			cin.clear();
		}
		if (!valid)
		{
			clrscr(currentPos);
		}
	}

	return option;
}

Date dateInput(string question) 
{

	Date d;
	bool valid = false;
	unsigned day, month, year;

	string prov;

	cout << question << endl;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!valid)
	{
		day = intInput("   - Day: ");
		month = intInput("   - Month: ");
		year = intInput("   - Year: ");
		cin.clear();
		try
		{
			d = Date(day, month, year);
			valid = true;
		}
		catch (...)
		{
			valid = false;
			// Apenas para windows...
			//MessageBoxA(NULL, "    Invalid Date            ", "Error!", MB_OK);
		}
		if (!valid)
		{
			clrscr(currentPos);
		}
	}
	return d;
}

ageRange ageRangeInput(string question)
{

	ageRange ageR;
	bool valid = false;
	int minAge, maxAge;

	string prov;

	cout << question << endl;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!valid)
	{
		minAge = intInput("   - Minimum age: ");
		maxAge = intInput("   - Maximum age: ");
		cin.clear();
		if(minAge > maxAge)
		{
			valid = false;
			// Apenas para windows...
			MessageBoxA(NULL, "    Min Age is greater than Max Age       ", "Error!", MB_OK);
		}
		else
		{
			valid = true;
			ageR.maxAge = maxAge;
			ageR.minAge = minAge;
		}
		if (!valid)
		{
			clrscr(currentPos);
		}
	}
	return ageR;
}

/**
* Robustness of the menu Input:
* - Checks if the input number is inside the menu option bounds
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for the option number
* @param	inferiorLimit	Lower possible option in the menu
* @param	superiorLimit	Higher possible option in the menu
*
* @return	int				Integer with the desired option
*
* @see		getlineZ		(@		ConsoleFunctions)
*/
int menuInput(string question, int inferiorLimit, int superiorLimit)
{
	string option;
	bool ValidInput = false;
	int option_number;

	cout << question;

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentPos = GetConsoleCursorPosition(hCon);

	while (!ValidInput)
	{
		cin.clear();

		bool ErrorFlag = false;

		getlineZ(cin, option);


		if (cin.eof())
		{
			cin.clear();
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			ErrorFlag = true;
		}
		if (option == "")
		{
			ErrorFlag = true;
		}
		else
		{
			if (option.length() > 0) {
				for (size_t i = 0; i < option.length(); i++)
				{
					if (!isdigit((unsigned char)option.at(i)))
					{
						ErrorFlag = true;
						break;
					}
				}
			}
			if(!ErrorFlag)
				option_number = stoi(option);

			if (!ErrorFlag && !(option_number >= inferiorLimit && option_number <= superiorLimit))
			{
				ErrorFlag = true;
			}
		}

		ValidInput = !ErrorFlag;

		if (ErrorFlag)
		{

			clrscr(currentPos);
		}

	}

	return option_number;
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

	cout << " Plataform :" << endl << endl;

	cout << "   1 - PC" << endl;

	cout << "   2 - PS4" << endl;
	
	cout << "   3 - XBOX" << endl;

	cout << "   0 - All the Plataforms" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);
	
	switch (option_number)
	{
	case 0:
		return all_platforms;
	case 1:
		return pc;
	case 2:
		return ps4;
	case 3:
		return xbox;
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
	if (!isOnline)
		if(platform != all_platforms){
			gL.addTitle(new HomeTitle(name, price, releaseDate, ar, platform, genre, company));
			return;
		}
		else
		{
			for (int plat = pc; plat != all; plat++)
			{
				gL.addTitle(new HomeTitle(name, price, releaseDate, ar, static_cast<gameLibraryPlatform>(plat), genre, company));
			}
			return;
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
				for (int plat = pc; plat != all; plat++)
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
				for (int plat = pc; plat != all; plat++)
				{
					gL.addTitle(new OnlineTitle(name, price, releaseDate, ar, static_cast<gameLibraryPlatform>(plat), genre, company, new DynamicSubscription(subsPrice)));
				}
				return;
			}
		}
	}

}

void SecondMenu(GameLibrary & gameL)
{
	int option_number;

	cout << " Do you want to:" << endl << endl;

	cout << "   1 - Add a new Game" << endl;

	cout << "   2 - Add a new User" << endl;
	//TODO: Nao gosto mas é para poder ver os jogos, jogar, comprar...
	cout << "   3 - Login as a User" << endl;

	cout << "   4 - Make a List/Ranking" << endl;

	cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		header("Add New Game");
		addGames(gameL);
		cout << endl << endl;
		SecondMenu(gameL);
		break;

	case 2:
		header("Add New User");
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
		FirstMenu();
		break;
	}
}

void FirstMenu()
{
	GameLibrary gl = GameLibrary();

	int option_number;

	cout << " OPTIONS:" << endl << endl;

	cout << "   1 - Create Library Manually" << endl;

	cout << "   2 - Load Library" << endl;

	cout << "   0 - Exit" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 2);

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
	case 0:
		system("cls");
		return;
	}
	
	SecondMenu(gl);
}

int main() {	
	system("title   GAME LIBRARY");
	mainHeader("Welcome to the Game Library");
	
	FirstMenu();





	return 0;
}
