#include "Title.h"
#include <algorithm>
#include "..\Utilities\Exceptions.h"

using namespace std;

unsigned int Title::nextTitleID = 0;

Title::Title(string name, double price, Date releaseDate, ageRange ageR, string platform, string genre, string company) : titleID(++nextTitleID), releaseDate(releaseDate)
{
	// TODO: Fazer throw já aqui se nome já existente ou apenas na library
	this->name = name;
	basePrice = price;
	this->ageR = ageR;
	// TODO: Fazer pertencer a tipo de plataforma e género??
	this->platform = platform;
	this->platform = genre;
	this->platform = company;
}

const Sale & Title::getLastSale() const
{
	if (0 == pricesHistory.size())
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
	return pricesHistory.at(pricesHistory.size() - 1);
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

void Title::addPromotion(Sale & promotion) {
	if (promotion.getEndDate() < Date::getCurrentDate())
	{
		throw ExpiredSale(promotion.getEndDate());
	}
	if(0 == pricesHistory.size() || getLastSale().getEndDate() < promotion.getStartDate())
		pricesHistory.push_back(promotion);
	else if (promotion.getStartDate() < pricesHistory.at(0).getStartDate())
	{
		//TODO: maneira mais eficiente de acrescentar ao início??
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

bool Title::operator<(const Title & t2) const
{
	return getTitleID() < t2.getTitleID();
}
