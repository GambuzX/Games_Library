#ifndef TITLE_H
#define TITLE_H

#include <string>
#include <vector>
#include "..\Utilities\Date.h"
#include "..\Utilities\Sale.h"
#include "..\Utilities\Update.h"

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

	virtual const std::vector<Update> & getUpdates() const = 0;
	virtual void getStats() const = 0;
	virtual void UpdateTitle(Update *) = 0;

	std::string getName() const { return name; };
	unsigned int getTitleID() const { return titleID; };
	double getBasePrice() const { return basePrice; };
	Date getReleaseDate() const { return releaseDate; };
	ageRange getAgeRange() const { return ageR; };
	std::string getPlatform() const { return platform; };
	std::string getGenre() const { return genre; };
	std::string getCompany() const { return company; };
	const Sale & getLastSale() const;
	double getCurrentPrice(Date & date) const;

	// TODO: Acho que set's neste faz sentido pq j� tem cenas associadas (podes s� querer mudar plat, gen ou emp a n�o ser que const)

	void addPromotion(Sale & promotion);

	// Necessary for the set
	bool operator<(const Title& t2) const;
};

#endif
