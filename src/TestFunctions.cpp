#include <iostream>
#include "Utilities\Date.h"

using namespace std;

int main() {
	Date d1(1, 4, 2015);
	Date d2(2, 3, 2016);

	cout << d2 - d1 << endl;
	
	return 0;
}