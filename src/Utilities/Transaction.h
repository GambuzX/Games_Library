#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Date.h"
#include <string>

/** @defgroup Transaction Transaction Class
 * @{
 *
 * Transaction Class represents the different types of transactions possible to be done by the user
 * Each object has a date of the transaction, an enum corresponding to a transation type and a value
 * Each User should have a Transaction vector
 * 
 * @see User
 * @see Date
 */

/**
 * @brief Enumerated type for identifying the different types of transactions possible
 */
enum TransactionType {
	gamePurchase,		/*!< Purchase a Game Transaction */ 
	homeUpdate,			/*!< Update a Home Title Transaction */ 
	onlineSubscription	/*!< Paying the Subscription of an Online Game Transaction */ 
};

class Transaction {

private:
	double value; /**< @brief Value of the Transaction */
	Date date; /**< @brief Date when the Transaction was made */
	TransactionType type; /**< @brief Type of the Transaction */

public:
	/**
	 * @brief Construct a new Transaction object with the Present Date
	 * 
	 * @param val Double to initialize the value Private Member
	 * @param t TransactionType to initialize the type Private Member
	 */
	Transaction(double val, TransactionType t);

	/**
	 * @brief Construct a new Transaction object with the desired date
	 * 
	 * @param val Double to initialize the value Private Member
	 * @param d Date that initializes the date Private Member
	 * @param t TransactionType to initialize the type Private Member
	 */
	Transaction(double val, Date d, TransactionType t);
	
	/**
	 * @brief Get the Value Private Member
	 * 
	 * @return double Returns the value Private Member
	 */
	double getValue() const;

	/**
	 * @brief Get the Date object
	 * 
	 * @return Date Returns the Date object
	 */
	Date getDate() const;

	/**
	 * @brief Get the Type Private Member
	 * 
	 * @return TransactionType Returns the type Private Member
	 */
	TransactionType getType() const;

	/**
	* @brief Overload of the operator <<
	*
	* @param os Output stream
	* @param trans Transaction to send to ostream
	* @return ostream& Output stream passed as argument
	*/
	friend std::ostream & operator<<(std::ostream & os, const Transaction & trans);
};

/** @} */

#endif
