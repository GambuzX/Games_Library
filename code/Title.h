#ifndef TITLE_H
#define TITLE_H

class Title {

private:
	int ID;
	String name;
	float basePrice;
	Date releaseDate;
	String platform;
	String genre;
	String company;
	vector<Promotion> pricesHistory;
	int minAge;
	int maxAge;

public:
	Title();

	int getID();

	void getName();

	void getBasePrice();

	void getReleaseDate();

	void getPlatform();

	void getGenre();

	void getCompany();

	void getMinAge();

	void getMaxAge();

	void addPromotion();

	void getCurrentPrice();

	void setBasePrice();
};

#endif
