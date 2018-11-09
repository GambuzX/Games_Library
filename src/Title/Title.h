#ifndef TITLE_H
#define TITLE_H

class Title {

private:
	unsigned int titleID;
	string name;
	double basePrice;
	Date releaseDate;
	unsigned int minAge;
	string platform;
	string genre;
	string company;
	vector<Sale> pricesHistory;
	int attribute;

public:
	Title(string name, double price, Date releaseDate, range ageRange);

	void addUpdate(Update update);

	virtual void getInfo() = 0;

	void addPromotion();
};

#endif
