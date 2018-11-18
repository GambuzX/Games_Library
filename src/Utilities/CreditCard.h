#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <string>
#include "Date.h"

/** @defgroup CreditCard Credit Card Class
 * @{
 *
 * Credit Card Class represents a credit card with a number, an holder name, an Expiration Date and the balance
 * Every user should have at least one in order to buy, play and update his games
 * 
 * @see User
 * @see Date
 */
class CreditCard {

private:
	std::string number; /**< @brief String with the Credit Card Number */
	std::string holder; /**< @brief String with the Credit Card Holder Name */
	Date expiryDate; /**< @brief Expiration Date of the Credit Card */
	double balance; /**< @brief Balance of the Credit Card */

public:
	/**
	 * @brief Construct a new Credit Card object
	 * May throw exceptions if the Credit Card you are trying to create has a negative balance
	 * 
	 * @param n String that initializes the number Private Member
	 * @param h String that initializes the holder Private Member
	 * @param exp Date that initializes the expiryDate Private Member
	 * @param bal Double that initializes the balance Private Member
	 * @throw NegativeFunds()
	 */
	CreditCard(std::string n, std::string h, Date exp, double bal);

	/**
	 * @brief Get the Number Private Member
	 * 
	 * @return string Returns the number Private Member
	 */
	std::string getNumber() const { return number; }
	/**
	 * @brief Get the Holder Private Member
	 * 
	 * @return string Returns the holder Private Member
	 */
	std::string getHolder() const { return holder; }
	/**
	 * @brief Get the Expiry Date object
	 * 
	 * @return string Returns the expiryDate object
	 */
	Date getExpiryDate() const { return expiryDate; }
	/**
	 * @brief Get the Balance Private Member
	 * 
	 * @return double Returns the balance Private Member
	 */
	double getBalance() const { return balance; }

	/**
	 * @brief Function to Add money to the Credit Card
	 * 
	 * @param funds Amount of money that you want to add to your balance
	 * @return double Returns the final Balance of the Credit Card
	 */
	double addFunds(double funds);
	/**
	 * @brief Function to Remove money from the Credit Card
	 * May throw some exceptions if the amount you are trying to take away is bigger than the current balance
	 * 
	 * @param funds Amount of money that you want to remove from your Credit Card
	 * @return double Returns the final Balance of the Credit Card
	 * @throw NegativeFunds()
	 */
	double removeFunds(double funds);
	/**
	 * @brief Removes all the funds of the Credit Card returning its balance to 0
	 * 
	 */
	void resetFunds();

	/**
	 * @brief Overload of the sum operator
	 * Adds the Value desired to the current Balance
	 * 
	 * @param val Amount of money that you wish to add to your credit card balance
	 * @return CreditCard& Returns the Credit Card with the funds added
	 * @see addFunds()
	 */
	CreditCard & operator+(const double & val);
	/**
	 * @brief Overload of the subtraction operator
	 * Removes the Value desired to the current Balance
	 * May throw some exceptions if the amount you are trying to take away is bigger than the current balance
	 * 
	 * @param val Amount of money that you wish to remove from your credit card balance
	 * @return CreditCard& Returns the Credit Card with the funds removed
	 * @see removeFunds()
	 * @throw NegativeFunds()
	 */
	CreditCard & operator-(const double & val);
};

/** @} */

#endif