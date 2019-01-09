#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Date.h"
#include <string>

/** @addtogroup UserUtility
* @{
*/

/**
 * @brief Enumerated type for identifying the different types of transactions possible
 */
enum TransactionType {
	gamePurchase,		/*!< Purchase a Game Transaction */ 
	homeUpdate,			/*!< Update a Home Title Transaction */ 
	onlineSubscription	/*!< Paying the Subscription of an Online Game Transaction */ 
};

/**
 * @brief Class that represents a Transaction
 */
class Transaction {

private:
	double value; /**< @brief Value of the Transaction */
	Date date; /**< @brief Date when the Transaction was made */
	TransactionType type; /**< @brief Type of the Transaction */
	unsigned int titleID;	/**< @brief ID of the Title of the Transaction */

public:
	/**
	 * @brief Construct a new Transaction object with the Present Date
	 * 
	 * @param val Double to initialize the value Private Member
	 * @param t TransactionType to initialize the type Private Member
	 * @param titleID ID of the title of the transaction
	 */
	Transaction(double val, TransactionType t, unsigned int id);

	/**
	 * @brief Construct a new Transaction object with the desired date
	 * 
	 * @param val Double to initialize the value Private Member
	 * @param d Date that initializes the date Private Member
	 * @param t TransactionType to initialize the type Private Member
	 * @param titleID ID of the title of the transaction
	 */
	Transaction(double val, Date d, TransactionType t, unsigned int id);
	
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
	 * @return TransactionType Returns the titleID Private Member
	 */
	TransactionType getType() const;

	/**
	 * @brief Get the Title ID Private Member
	 *
	 * @return unsigned int Returns the type Private Member
	 */
	unsigned int getTitleID() const;

	/**
	* @brief Overload of the operator <<
	*
	* @param os Output stream
	* @param trans Transaction to send to ostream
	* @return ostream& Output stream passed as argument
	*/
	friend std::ostream & operator<<(std::ostream & os, const Transaction & trans);

	/**
	* @brief Overload of the < operator
	* Compares by the date of the Transaction
	*
	* @param t2 Second Transaction object to use in comparison
	* @return Result of comparison
	*/
	bool operator<(const Transaction& t2) const;

	/**
	 * @brief Write information on a Transaction in a friendly way
	 * to the ostream given as argument
	 *
	 * @param os ostream to write to
	 */
	void writeTransaction(std::ostream &os) const;
};

/** @} */

#endif
