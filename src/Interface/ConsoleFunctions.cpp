#include "ConsoleFunctions.h"

using namespace std;

//=======================================================================================================================//

void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

//=======================================================================================================================//

void setcolor(unsigned int color, unsigned int background_color)
{
	// Only changes to and from balck to gray

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	// 0 = BLACK
	if (background_color == 0)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

//=======================================================================================================================//

void lineAcrossConsole(char lineChar)
{
	// Change to autoadjust??

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	for (int i = 0; i < columns - 1; i++)
	{
		cout << lineChar;
	}

	cout << endl;
}

//=======================================================================================================================//

void centerWord(string title)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, space;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	space = (columns - title.size()) / 2;

	for (int i = 0; i < space; i++)
	{
		cout << " ";
	}

	cout << title.c_str() << endl;	
}

//=======================================================================================================================//

void clrscr(COORD coordScreen)
{
	//COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

//=======================================================================================================================//

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

//=======================================================================================================================//

istream& getlineZ(istream& stream, string& str)
{
	char ch;
	str.clear();
	while (stream.get(ch) && ch != '\n' && ch != (char)26) {
		str.push_back(ch);
	}
	if (ch != '\n')
	{
		str.clear();
	}
	return stream;
}

//=======================================================================================================================//