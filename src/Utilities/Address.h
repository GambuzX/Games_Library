#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>


/** @defgroup Address Address Class
 * @{
 *
 * Address Class representing an Address constituted by an House Number, Street Name, City and Coutry
 * Used mainly by the User
 * 
 * @see User
 */
class Address {

private:
	unsigned int houseNumber; /**< @brief Number of the house */
	std::string streetName; /**< @brief Name of the Street where the House is */
	std::string city; /**< @brief City where the house is located */
	std::string country; /**< @brief Country Name */
public:
	/**
	 * @brief Construct a new Address object
	 * Initializes strings to the empty string and the house number to 0
	 *  
	 */
	Address();
	/**
	 * @brief Construct a new Address object
	 * 
	 * @param houseNumber Unsigned int that initializes the private member with the same name to the string passed as parameter
	 * @param streetName String that initializes the private member with the same name to the string passed as parameter
	 * @param city String that initializes the private member with the same name to the string passed as parameter
	 * @param country  String that initializes the private member with the same name to the string passed as parameter
	 */
	Address(unsigned int houseNumber, std::string streetName, std::string city, std::string country);
	/**
	 * @brief Construct a new Address object
	 * 
	 * @param add Address used to construct other Address with the same parameters
	 */
	Address(const Address & add);

	/**
	 * @brief Get the House Number Private Member
	 * 
	 * @return unsigned int Returns House Number Private Member
	 */
	unsigned int getHouseNumber() const { return houseNumber; };
	/**
	 * @brief Get the Street Name Private Member
	 * 
	 * @return string Returns Street Name Private Member
	 */
	std::string getStreetName() const { return streetName; };
	/**
	 * @brief Get the City Private Member
	 * 
	 * @return string Returns City Private Member
	 */
	std::string getCity() const { return city; };
	/**
	 * @brief Get the Country Private Member
	 * 
	 * @return string Returns Country Private Member
	 */
	std::string getCountry() const { return country; };

	/**
	 * @brief Set the House Number Private Member
	 * 
	 * @param houseNumber Unsigned int to be set to the House Number Private Member
	 */
	void setHouseNumber(unsigned int houseNumber) { this->houseNumber = houseNumber; };
	/**
	 * @brief Set the Street Name Private Member
	 * 
	 * @param streetName String to be set to the Street Name Private Member
	 */
	void setStreetName(std::string streetName) { this->streetName = streetName; };
	/**
	 * @brief Set the City Private Member
	 * 
	 * @param city String with the city name to be set to the City Private Member
	 */
	void setCity(std::string city) { this->city = city; };
	/**
	 * @brief Set the Country Private Member
	 * 
	 * @param country String with the country name to be set to the Country Private Member
	 */
	void setCountry(std::string country) { this->country = country; };

	/**
	 * @brief Function that evaluates whether two houses are from the same Country
	 * 
	 * @param a2 Address with which we are comparing the Current Address
	 * @return true If the two addresses have the same Country
	 * @return false If the two addresses are of different Countries
	 */
	bool sameCountry(const Address & a2) const;
	/**
	 * @brief Function that evaluates whether two houses are from the same City
	 * 
	 * @param a2 Address with which we are comparing the Current Address
	 * @return true If the two addresses have the same City (and Country)
	 * @return false If the two addresses are of different Cities
	 * @see sameCountry()
	 */
	bool sameCity(const Address & a2) const;
	/**
	 * @brief Function that evaluates whether two houses are from the same Street
	 * 
	 * @param a2 Address with which we are comparing the Current Address
	 * @return true If the two addresses have the same Street Name (, City and Country)
	 * @return false If the two addresses are of different Streets
	 * @see sameCity()
	 */
	bool sameStreet(const Address & a2) const;
	/**
	 * @brief Equal overload that evaluates whether two houses are the same
	 * 
	 * @param a2 Address with which we are comparing the Current Address
	 * @return true  If the two addresses are equal (have the same House Number, Street Name, City and Country)
	 * @return false If the two addresses are different
	 * @see sameStreet()
	 */
	bool operator==(const Address & a2) const;

	/**
	 * @brief Overload insertion operator to output formated Address
	 * 
	 * @param os Output stream object where characters are inserted
	 * @param a Formated Address to insert/output
	 * @return ostream& The ostream object (os) passed as parameter
	 */
	friend std::ostream & operator<<(std::ostream & os, const Address & a);
};

/** @} */

#endif
