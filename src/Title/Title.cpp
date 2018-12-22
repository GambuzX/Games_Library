#include "Title.h"
#include <algorithm>
#include "..\Utilities\Exceptions.h"
#include "..\GameLibrary.h"

using namespace std;

unsigned int Title::nextTitleID = 0;

Title::Title(string name, double price, Date releaseDate, ageRange ageR, gameLibraryPlatform platform, gameLibraryGenre genre, string company) : titleID(++nextTitleID), releaseDate(releaseDate)
{
	this->name = name;
	basePrice = price;
	this->ageR = ageR;
	this->platform = platform;
	this->genre = genre;
	this->company = company;
}

const Sale & Title::getLastSale() const
{
	if (pricesHistory.empty())
		throw InexistentSale();
	/*
	Date lastEndDate = pricesHistory.at(0).getEndDate();
	unsigned int lastSaleInd = 0;
	for (size_t i = 0; i < pricesHistory.size(); i++) 
		if (lastEndDate < pricesHistory.at(i).getEndDate()){
			lastEndDate = pricesHistory.at(i).getEndDate();
			lastSaleInd = i;
		}
	
	return pricesHistory.at(lastSaleInd);
	*/
	return pricesHistory.back();
}

const Sale & Title::getSaleOn(Date & date) const
{
	for (size_t i = 0; i < pricesHistory.size(); i++)
	{
		if (pricesHistory.at(i).isActiveOn(date))
		{
			return pricesHistory.at(i);
		}
	}
	throw InexistentSale(date);
}

double Title::getCurrentPrice(Date & date) const
{
	for (size_t i = 0; i < pricesHistory.size(); i++)
	{
		if (pricesHistory.at(i).isActiveOn(date))
		{
			return basePrice * pricesHistory.at(i).getSaleFactor();
		}
	}
	return basePrice;
}

void Title::addPromotion(Sale promotion) {
	if (promotion.getEndDate() < GameLibrary::getLibraryDate())
	{
		throw ExpiredSale(promotion.getEndDate());
	}
	if(pricesHistory.empty() || getLastSale().getEndDate() < promotion.getStartDate())
		pricesHistory.push_back(promotion);
	else if (promotion.getStartDate() < pricesHistory.at(0).getStartDate())
	{
		pricesHistory.push_back(promotion);
		sort(pricesHistory.begin(), pricesHistory.end());
	}
	else {
		for (size_t i = 0; i < pricesHistory.size() - 1; i++)
			// Avoid Sales Overlap
			if ((pricesHistory.at(i).getEndDate() < promotion.getStartDate()) && (promotion.getEndDate() < pricesHistory.at(i + 1).getStartDate())) {
				pricesHistory.push_back(promotion);
				sort(pricesHistory.begin(), pricesHistory.end());
				return;
			}
		throw OverlappingSales();
	}
}

void Title::removePromotion(Date & saleBeginning)
{
	if (saleBeginning < GameLibrary::getLibraryDate())
	{
		throw SaleStarted(saleBeginning);
	}
	for (size_t i = 0; i < pricesHistory.size(); i++)
		if (saleBeginning == pricesHistory.at(i).getStartDate()) {
			pricesHistory.erase(pricesHistory.begin() + i);
			return;
		}
	throw InexistentSale(saleBeginning);
}

bool Title::operator<(const Title & t2) const
{
	return getTitleID() < t2.getTitleID();
}

ostream &operator<<(ostream &os, const Title &title)
{
	os << title.getTitleID() << " " << title.getName() << endl;
	os << title.getPlatform() << " " << title.getGenre() << endl;
	os << title.getAgeRange().minAge << " " << title.getAgeRange().maxAge << endl;
	os << title.getReleaseDate() << endl;
	return os;
}

void Title::displayTitleInfo(std::ostream &os)
{
	os << getTitleID() << " " << getName() << endl;
	os << getBasePrice() << " " << getCompany() << endl;
	os << getPlatform() << " " << getGenre() << endl;
	os << getAgeRange().minAge << " " << getAgeRange().maxAge << endl;
	os << getReleaseDate() << endl;
}
