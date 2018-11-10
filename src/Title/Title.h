#ifndef TITLE_H
#define TITLE_H

class Title {

private:
	static int nextTitleID;
	unsigned int titleID;
	string name;
	double basePrice;
	Date releaseDate;
	unsigned int minAge;
	string platform;
	string genre;
	string company;
	vector<Sale> pricesHistory;

public:
	Title(string name, double price, Date releaseDate, range ageRange);

	virtual void getInfo() = 0;

	virtual void getStats() = 0;

	double getCurrentPrice();

	void addPromotion();
};

#endif
