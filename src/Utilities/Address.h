#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {

private:
	int houseNumber;
	std::string streetName;
	std::string city;
	std::string country;
	//std::string state;
public:
	Address();
	//Address(std::string streetName, std::string city, std::string country, std::string state);
	Address(int houseNumber, std::string streetName, std::string city, std::string country);

	int getHouseNumber() const { return houseNumber; };
	std::string getStreetName() const { return streetName; };
	std::string getCity() const { return city; };
	std::string getCountry() const { return country; };
	//std::string getState() const { return state; };

	void setHouseNumber(int houseNumber) { this->houseNumber = houseNumber; };
	void setStreetName(std::string streetName) { this->streetName = streetName; };
	void setCity(std::string city) { this->city = city; };
	void setCountry(std::string country) { this->country = country; };
	//void setState(std::string state) { this->state = state; };

	bool sameCountry(const Address & a2) const;
	bool sameCity(const Address & a2) const;
	bool sameStreet(const Address & a2) const;
	bool operator==(const Address & c2) const;

	friend std::ostream & operator<<(std::ostream & os, const Address & a);
};

#endif
