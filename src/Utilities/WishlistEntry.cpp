#include <ostream>
#include "WishlistEntry.h"

WishlistEntry::WishlistEntry(unsigned interest, float buyChance, Title* title)
{
	this->interest = (interest > 10 ? 10 : interest);
	this->buyChance = (buyChance >= 0 && buyChance <= 1) ? buyChance : 0;
	this->title = title;
}

void WishlistEntry::setInterest(unsigned interest)
{
	this->interest = (interest > 10 ? 10 : interest);
}

void WishlistEntry::setBuyChance(float buyChance)
{
	this->buyChance = (buyChance >= 0 && buyChance <= 1) ? buyChance : 0;
}

bool WishlistEntry::operator<(const WishlistEntry &ref) const
{
	if (interest == ref.getInterest())
		return buyChance < ref.getBuyChance();
	return interest < ref.getInterest();
}

std::ostream &operator<<(std::ostream &out, const WishlistEntry &we1)
{
	out << we1.getTitle();
	out << "Interest: " << we1.getInterest() << std::endl;

	return out;
}
