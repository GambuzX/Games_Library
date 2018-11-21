#include "Input.h"
#include "ConsoleFunctions.h"
#include <sstream>
#include <limits>

using namespace std;

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
		if (name.empty() || !letterFlag)
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
		if (name.empty() || !letterFlag)
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

unsigned int intInput(string question)
{
	unsigned int option;
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

	ageRange ageR{};
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
		if (minAge > maxAge)
		{
			valid = false;
			// Apenas para windows...
			MessageBoxA(nullptr, "    Min Age is greater than Max Age       ", "Error!", MB_OK);
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
		if (option.empty())
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
			if (!ErrorFlag)
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
