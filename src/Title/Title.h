#ifndef TITLE_H
#define TITLE_H

#include <string>
#include <vector>
#include "..\Utilities\Date.h"
#include "..\Utilities\Sale.h"

struct ageRange {
	int minAge;
	int maxAge;
};

class Title {

private:
	static unsigned int nextTitleID;
	const unsigned int titleID;
	std::string name;
	double basePrice;
	const Date releaseDate;
	ageRange ageR;
	std::string platform;
	std::string genre;
	std::string company;
	// Sorted by begin date mudar para estrutura ordenada??
	std::vector<Sale> pricesHistory;

public:
	Title(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);

	virtual void getUpdates() = 0;
	virtual void getStats() = 0;

	std::string getName() const { return name; };
	unsigned int getTitleID() const { return titleID; };
	double getBasePrice() const { return basePrice; };
	Date getReleaseDate() const { return releaseDate; };
	ageRange getAgeRange() const { return ageR; };
	std::string getPlataform() const { return platform; };
	std::string getGenre() const { return genre; };
	std::string getCompany() const { return company; };
	const Sale & getLastSale() const;
	double getCurrentPrice(Date & date) const;

	// TODO: Acho que set's neste faz sentido pq já tem cenas associadas (podes só querer mudar plat, gen ou emp a não ser que const)

	void addPromotion(Sale & promotion);

	// Necessary for the set
	bool operator<(const Title& t2) const;
};

class InexistentSale {
private:
	std::string message;
	//Date date;

public:
	InexistentSale() { message = "There is no existing sale!"; };
	/*InexistentSale(const Date & d1) {
		date = d1;
		std::ostringstream os;
		os << date;
		message = "There are no sales on " + os.str();
	}*/
	std::string getMessage() const { return message; };
	//Date getDate() const { return date; };
};

// TODO: Mudar parametros??
class OverlappingSales {
private:
	std::string message;

public:
	OverlappingSales() { message = "There are sales overlapping!"; };
	std::string getMessage() const { return message; };
};

class ExpiredSale {
private:
	Date endSalesDate;
	Date currentDate;

public:
	ExpiredSale() { currentDate = Date::getCurrentDate(); endSalesDate = Date(); };
	ExpiredSale(Date endSalesDate) { this->endSalesDate = endSalesDate; currentDate = Date::getCurrentDate(); };
	std::string getMessage() const { 
		std::ostringstream os1, os2;
		os1 << endSalesDate;
		os2 << currentDate;
		if (endSalesDate == Date()) return "Sale has expired: current date " + os2.str();
		return "Sale has expired: Sale ends in " + os1.str() + " and we are in " + os2.str();
	};
	Date getEndSalesDate() const { return endSalesDate; };
};

#endif
