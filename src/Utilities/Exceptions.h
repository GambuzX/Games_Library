#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <sstream>
#include "Date.h"
#include "Update.h"
#include "..\GameLibrary.h"

/** @defgroup Exceptions Exceptions
 * @ingroup GameLibrary
 * @{
 *
 * @brief Group holding information about all the exceptions that may be thrown by the Game Library
 *
 * Exceptions thrown by the classes inside of the Games Library
 *
 * @see GameLibrary
 * @see User
 * @see Title
 */

 /**
 * @brief Exception that is thrown when you try to update a Home Title to a previous version
 */
class OldUpdate
{
private:
	Update oldUpdate; /**< @brief Old update */
	Update currentVersion; /**< @brief Current update */

public:
	/**
	 * @brief Construct a new OldUpdate object
	 *
	 * @param oldUp Outdated Update that tried to be used
	 */
	OldUpdate(const Update & oldUp) { oldUpdate = oldUp; };

	/**
	 * @brief Construct a new OldUpdate object
	 *
	 * @param oldUp Outdated Update that tried to be used
	 * @param currUp Current Home Title Update
	 */
	OldUpdate(const Update & oldUp, const Update & currUp) { oldUpdate = oldUp; currentVersion = currUp; };

	/**
	 * @brief Get the oldUpdate Private Member
	 *
	 * @return Update Returns the oldUpdate Private Member
	 */
	Update getOldUpdate() const { return oldUpdate; };

	/**
	 * @brief Get the currentVersion Private Member
	 *
	 * @return Update Returns the currentVersion Private Member
	 */
	Update getCurrentVersion() const { return currentVersion; };

	/**
	 * @brief Get the error message
	 *
	 * @return string Error message
	 */
	std::string getMessage() const
	{
		std::ostringstream oss;
		oss << oldUpdate.getVersion();
		if (currentVersion == Update())
			return "Tried to add old Update: " + oss.str();
		std::string msg = "Tried to add old Update: " + oss.str() + " while Current Version is: ";
		oss.str("");
		oss << currentVersion.getVersion();
		return msg + oss.str();
	};
};

 /**
 * @brief Exception that is thrown when a Home Title method is called on an Online Title
 */
class NotHomeTitle
{
private:
	unsigned titleID; /**< @brief ID of title */
public:
	/**
	 * @brief Construct a new NotHomeTitle object
	 *
	 * @param id ID of Title that is not a Home Title
	 */
	explicit NotHomeTitle(unsigned id) { titleID = id; }

	/**
	 * @brief Get the titleID Private Member
	 *
	 * @return unsigned Returns the titleID Private Member
	 */
	unsigned getTitleID() { return titleID; }
};

/**
* @brief Exception that is thrown when an Online Title method is called on a Home Title
*/
class NotOnlineTitle
{
private:
	unsigned titleID; /**< @brief ID of title */
public:
	/**
	 * @brief Construct a new NotOnlineTitle object
	 *
	 * @param id ID of Title that is not an Online Title
	 */
	explicit NotOnlineTitle(unsigned id) { titleID = id; }

	/**
	 * @brief Get the titleID Private Member
	 *
	 * @return unsigned Returns the titleID Private Member
	 */
	unsigned getTitleID() { return titleID; }
};


 /**
 * @brief Exception that is thrown when you check for a Sale in a Date that has none
 */
class InexistentSale
{
private:
	std::string message; /**< @brief error message */
	Date date; /**< @brief Date that was checked */

public:
	/**
	 * @brief Construct a new InexistentSale object
	 * Initializes it with an error message
	 */
	InexistentSale() { message = "There is no existing sale!"; date = Date(); };

	/**
	 * @brief Construct a new InexistentSale object
	 * Initializes it with an error message

	 * @param d1 Date that was checked for a Sale
	 */
	explicit InexistentSale(const Date & d1) {
		date = d1;
		std::ostringstream os;
		os << date;
		message = "There are no sales on " + os.str();
	}

	/**
	 * @brief Get the message Private Member
	 *
	 * @return string Returns the message Private Member
	 */
	std::string getMessage() const { return message; };

	/**
	 * @brief Get the date Private Member
	 *
	 * @return Date Returns the date Private Member
	 */
	Date getDate() const { return date; };
};

 /**
 * @brief Exception that is thrown when there are Sales for the same Title overlapping
 */
class OverlappingSales
{
private:
	std::string message; /**< @brief error message */

public:
	/**
	 * @brief Construct a new OverlappingSales object
	 * Initializes it with an error message
	 */
	OverlappingSales() { message = "There are sales overlapping!"; };

	/**
	 * @brief Get the message Private Member
	 *
	 * @return string Returns the message Private Member
	 */
	std::string getMessage() const { return message; };
};


 /**
 * @brief Exception that is thrown when a Sale has already expired
 */
class ExpiredSale
{
private:
	Date endSalesDate; /**< @brief Date when the Sale expired */
	Date currentDate; /**< @brief Current Date */

public:
	/**
	 * @brief Construct a new ExpiredSale object
	 * Initializes it with the current date
	 */
	ExpiredSale() { currentDate = GameLibrary::getLibraryDate(); endSalesDate = Date(); };

	/**
	 * @brief Construct a new ExpiredSale object
	 * Initializes it with the current date
	 *
	 * @param endSalesDate Date when the Sale expired
	 */
	explicit ExpiredSale(Date endSalesDate) { this->endSalesDate = endSalesDate; currentDate = GameLibrary::getLibraryDate(); };

	/**
	 * @brief Get an error message
	 *
	 * @return string Returns an error message
	 */
	std::string getMessage() const
	{
		std::ostringstream os1, os2;
		os1 << endSalesDate;
		os2 << currentDate;
		if (endSalesDate == Date()) return "Sale has expired: current date " + os2.str();
		return "Sale has expired: Sale ends in " + os1.str() + " and we are in " + os2.str();
	};

	/**
	 * @brief Get the endSalesDate Private Member
	 *
	 * @return Date Returns the endSalesDate Private Member
	 */
	Date getEndSalesDate() const { return endSalesDate; };
};

 /**
 * @brief Exception that is thrown when a Sale has already started and you try to remove it
 */
class SaleStarted
{
private:
	Date beginSalesDate; /**< @brief Date when the Sale started */
	Date currentDate; /**< @brief Current Date */

public:
	/**
	 * @brief Construct a new SaleStarted object
	 * Initializes it with the current date
	 */
	SaleStarted() { currentDate = GameLibrary::getLibraryDate(); beginSalesDate = Date(); };

	/**
	 * @brief Construct a new SaleStarted object
	 * Initializes it with the current date
	 *
	 * @param beginSalesDate Date when the Sale started
	 */
	explicit SaleStarted(Date beginSalesDate) { this->beginSalesDate = beginSalesDate; currentDate = GameLibrary::getLibraryDate(); };

	/**
	 * @brief Get an error message
	 *
	 * @return string Returns an error message
	 */
	std::string getMessage() const
	{
		std::ostringstream os1, os2;
		os1 << beginSalesDate;
		os2 << currentDate;
		if (beginSalesDate == Date()) return "Sale has started: current date " + os2.str();
		return "Sale has started: Sale started on " + os1.str() + " and we are in " + os2.str();
	};

	/**
	 * @brief Get the beginSalesDate Private Member
	 *
	 * @return Date Returns the beginSalesDate Private Member
	 */
	Date getBeginSalesDate() const { return beginSalesDate; };
};

 /**
 * @brief Exception that is thrown when a month is invalid
 */
class InvalidMonth
{
private:
	unsigned int month; /**< @brief invalid month value */

public:
	/**
	 * @brief Construct a new InvalidMonth object
	 * Sets it to the default constructor
	 */
	InvalidMonth() = default;

	/**
	 * @brief Construct a new InvalidMonth object
	 *
	 * @param m Month that is invalid
	 */
	explicit InvalidMonth(const unsigned int m) { month = m; };

	/**
	 * @brief Get the month Private Member
	 *
	 * @return unsigned Returns the month Private Member
	 */
	unsigned getMonth() const { return month; };
};

/**
* @brief Exception that is thrown when a day is invalid
*/
class InvalidDay
{
private:
	unsigned int day; /**< @brief invalid day value */

public:
	/**
	 * @brief Construct a new InvalidDay object
	 * Sets it to the default constructor
	 */
	InvalidDay() = default;

	/**
	 * @brief Construct a new InvalidDay object
	 *
	 * @param d Day that is invalid
	 */
	explicit InvalidDay(const unsigned int d) { day = d; };

	/**
	 * @brief Get the day Private Member
	 *
	 * @return unsigned Returns the day Private Member
	 */
	unsigned getDay() const { return day; };
};

/**
* @brief Exception that is thrown when a year is invalid
*/
class InvalidYear
{
private:
	unsigned int year; /**< @brief invalid year value */

public:
	/**
	 * @brief Construct a new InvalidYear object
	 * Sets it to the default constructor
	 */
	InvalidYear() = default;

	/**
	 * @brief Construct a new InvalidYear object
	 *
	 * @param y Year that is invalid
	 */
	explicit InvalidYear(const unsigned int y) { year = y; };

	/**
	 * @brief Get the year Private Member
	 *
	 * @return unsigned Returns the year Private Member
	 */
	unsigned getYear() const { return year; };
};

/**
* @brief Exception that is thrown when a Date is specified in an invalid format
*/
class InvalidDateFormat
{
private:
	std::string date; /**< @brief invalid date format */

public:
	/**
	 * @brief Construct a new InvalidDateFormat object
	 * Sets it to the default constructor
	 */
	InvalidDateFormat() = default;

	/**
	 * @brief Construct a new InvalidDateFormat object
	 *
	 * @param d Invalid Date format that was provided
	 */
	explicit InvalidDateFormat(const std::string d) { date = d; };

	/**
	 * @brief Get the date Private Member
	 *
	 * @return string Returns the date Private Member
	 */
	std::string getInvalidDate() const { return date; };
};

// TODO: comentar
class OldDate {
private:
	Date invDate;
public:
	explicit OldDate(const Date & d) { invDate = d; };
	Date getOldDate() const { return invDate; };

};

 /**
 * @brief Exception that is thrown when a Credit Card has negative funds
 */
class NegativeFunds
{
private:
	double funds; /**< @brief Invalid funds value */
public:
	/**
	 * @brief Construct a new NegativeFunds object
	 *
	 * @param f Invalid funds value
	 */
	explicit NegativeFunds(double f) : funds(f) {}

	/**
	 * @brief Get the funds Private Member
	 *
	 * @return double Returns the funds Private Member
	 */
	double getFunds() const { return funds; }
};

 /**
 * @brief Exception that is thrown when a User tries to buy something he has no funds for
 */
class NotEnoughFunds
{
private:
	double funds; /**< @brief Invalid funds value */
public:
	/**
	 * @brief Construct a new NotEnoughFunds object
	 *
	 * @param f Invalid funds value
	 */
	explicit NotEnoughFunds(double f) : funds(f) {}

	/**
	 * @brief Get the funds Private Member
	 *
	 * @return double Returns the funds Private Member
	 */
	double getFunds() const { return funds; }
};

 /**
 * @brief Exception that is thrown when you try to access a User's information in a Title that he does not own
 */
class InexistentUser
{
private:
	unsigned userID; /**< @brief User ID */
public:
	/**
	 * @brief Construct a new InexistentUser object
	 *
	 * @param id User ID
	 */
	explicit InexistentUser(unsigned id) { userID = id; }

	/**
	 * @brief Get the userID Private Member
	 *
	 * @return unsigned Returns the userID Private Member
	 */
	unsigned getUserID() { return userID; }
};

 /**
 * @brief Exception that is thrown when you try to add a repeated User to a Title's User Info map
 */
class DuplicatedUser
{
private:
	unsigned userID; /**< @brief User ID */
	std::string email; /**< @brief User email */
public:
	/**
	 * @brief Construct a new DuplicatedUser object
	 *
	 * @param id User ID
	 */
	explicit DuplicatedUser(unsigned id) { userID = id; }

	/**
	 * @brief Construct a new DuplicatedUser object
	 *
	 * @param mail User email
	 */
	DuplicatedUser(std::string mail) {  email = mail; }

	/**
	 * @brief Get the email Private Member
	 *
	 * @return string Returns the email Private Member
	 */
	std::string getEmail() { return email; }

	/**
	 * @brief Get the userID Private Member
	 *
	 * @return unsigned Returns the userID Private Member
	 */
	unsigned getUserID() { return userID; }
};

 /**
 * @brief Exception that is thrown when you try to update a User version that is already updated
 */
class TitleUpToDate
{
private:
	unsigned titleID; /**< @brief Title ID */
public:
	/**
	 * @brief Construct a new TitleUpToDate object
	 *
	 * @param id Title ID
	 */
	explicit TitleUpToDate(unsigned id) { titleID = id; }

	/**
	 * @brief Get the titleID Private Member
	 *
	 * @return unsigned Returns the titleID Private Member
	 */
	unsigned getTitleID() { return titleID; }
};

/**
* @brief Exception that is thrown when the Game Library was already loaded and tried to load again
*/
class AlreadyLoaded {
	std::string message = "Games Library was already loaded, please restart the program to load."; /**< @brief Error message */
public:
	/**
	* @brief Get the message Private Member
	*
	* @return string Returns the string Private Member
	*/
	std::string getMessage() const { return message; }
};

/**
* @brief Exception that is thrown when you try to find a WishlistEntry above a certain buyChance and it does not exist
*/
class NoMatchingWishlistEntry
{
	float buyChance; /**< @brief Buy chance */
public:
	/**
	* @brief Construct a new NoMatchingWishlistEntry object
	*
	* @param buyC Buy chance that was not matched
	*/
	NoMatchingWishlistEntry(float buyC) : buyChance(buyC) {}

	/**
	* @brief Get the buyChance Private Member
	*
	* @return float Returns the buyChance Private Member
	*/
	float getBuyChance() const { return buyChance; }
};

/** @} */


#endif