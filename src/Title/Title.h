#ifndef TITLE_H
#define TITLE_H

#include <string>
#include <vector>
#include "Date.h"
#include "Sale.h"

struct ageRange {
	int minAge;
	int maxAge;
}

class Title {

private:
	static int nextTitleID;
	unsigned int titleID;
	std::string name;
	double basePrice;
	Date releaseDate;
	ageRange ageR;
	std::string platform;
	std::string genre;
	std::string company;
	std::vector<Sale> pricesHistory;

public:
	Title(std::string name, double price, Date releaseDate, ageRange ageR);

	virtual void getInfo() = 0;

	virtual void getStats() = 0;

	double getCurrentPrice();

	void addPromotion();
};

#endif
