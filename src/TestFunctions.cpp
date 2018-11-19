#include <iostream>
#include <limits>
#include "Utilities\Date.h"
#include "GameLibrary.h"

using namespace std;

int main() {
	char option;
	string msg = "Games Library";
	auto decorator = string(msg.size(), '=');
	cout << decorator << endl << msg << endl << decorator << endl;


	cout << "Select an option: " << endl;
	cout << "0. Exit" << endl;
	cout << "1. Add title" << endl;

	cin >> option;

	switch (option) {
	case '1': {
		cout << "Connection to function not implemented yet" << endl;
		break;
	}
	case '0': exit(0);

	default:
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	GameLibrary gl = GameLibrary();

	return 0;
}