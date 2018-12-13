#include "WishlistEntry.h"

WishlistEntry::WishlistEntry(unsigned interest, float buyChance, Title* title)
{
	this->interest = (interest > 10 ? 10 : interest);
	this->buyChance = (buyChance >= 0 && buyChance <= 1) ? buyChance : 0;
	this->title = title;
}

bool WishlistEntry::operator<(const WishlistEntry &ref) const
{
	if (interest == ref.getInterest())
		return buyChance < ref.getBuyChance();
	return interest < ref.getInterest();
}