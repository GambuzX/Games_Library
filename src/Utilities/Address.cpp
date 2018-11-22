#include <ostream>
#include "Address.h"

using namespace std;

Address::Address()
{
	this->houseNumber = 0;
}

//Address::Address(string streetName, string city, string country, string state)
Address::Address(unsigned int houseNumber, string streetName, string city, string country)
{
	this->houseNumber = houseNumber;
	this->streetName = streetName;
	this->city = city;
	this->country = country;
	//this->state = state;
}

Address::Address(const Address & add) {
	houseNumber = add.getHouseNumber();
	streetName = add.getStreetName();
	city = add.getCity();
	country = add.getCountry();
}

bool Address::sameCountry(const Address & a2) const
{
	return this->country == a2.getCountry();
}

bool Address::sameCity(const Address & a2) const
{
	if (sameCountry(a2))
		return this->city == a2.getCity();
	return false;
}

bool Address::sameStreet(const Address & a2) const
{
	if (sameCity(a2))
		return this->streetName == a2.getStreetName();
	return false;
}

bool Address::operator==(const Address & a2) const
{
	if (sameStreet(a2))
		return this->houseNumber == a2.getHouseNumber();
	return false;
}

ostream & operator<<(ostream & os, const Address & a)
{
	os << " Street:\t\t" << a.getStreetName() << ", nº " << a.getHouseNumber() << endl;;
	os << " City:\t\t" << a.getCity() << endl;
	os << " Country:\t\t" << a.getCountry() << endl;
	return os;
}

void Address::writeAddress(ostream &os)
{
	os << getHouseNumber() << " " << getStreetName() << endl;
	os << getCity() << endl;
	os << getCountry() << endl;
}
