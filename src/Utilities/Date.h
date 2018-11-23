#ifndef DATE_H
#define DATE_H

#include <sstream>
#include <string>

/** 
* @ingroup TitleUtility
* @ingroup UserUtility
* @{
*/

/**
* @brief Class representing a Date in the format DD/MM/YYYY
*/
class Date {

private:
	unsigned int day; /**< @brief Day of the date */
	unsigned int month; /**< @brief Month of the date */
	unsigned int year; /**< @brief Year of the date */

	/**
	 * @brief Function that tells whether the paremeter is a leap year or not
	 * 
	 * @param year Unsigned int that we desire to know if it corresponds to a leap year
	 * @return true If the parameter corresponds to a leap year
	 * @return false If the parameter does not correspond to a leap year
	 */
	bool LeapYear(unsigned int year) const;
	/**
	 * @brief Function that returns the number of days in a certain month
	 * This function tests the year to see if it is a leap year
	 * Throws exception in case of invalid month
	 * 
	 * @param month Unsigned int corresponding to the month that we want to know the days from
	 * @param year Unsigned int to test if February should have 28 or 29 days
	 * @return unsigned int Number of days that the month has
	 * @throw InvalidMonth() If month is bigger than 12
	 * @see LeapYear()
	 */
	unsigned int daysInMonth(unsigned int month, unsigned int year) const;
	/**
	 * @brief Function that returns the number of days in a certain year
	 * 
	 * @param year Unsigned int representing a year that we desire to know the number of days
	 * @return unsigned int Number of days in the parameter year
	 * @see LeapYear()
	 */
	unsigned int daysInYear(unsigned int year) const;
	/**
	 * @brief Function that calculates the number that corresponds to the day specified
	 * May throw exceptions if it corresponds to a invalid date
	 * 
	 * @param day Day of the date that we which to turn into a number
	 * @param month  Month of the date that we which to turn into a number
	 * @param year Year of the date that we which to turn into a number
	 * @return unsigned int Between 1 and 366 that represents the day in the year
	 * @throw InvalidMonth() If month is bigger than 12
	 * @throw InvalidDay() If day is bigger than the days in the specified month
	 * @see daysInMonth()
	 */
	unsigned int dayNumber(unsigned int day, unsigned int month, unsigned int year) const;
	/**
	 * @brief Function that returns that number of days since year 0, month 1, day 1
	 * Helper function to subtraction between dates
	 * 
	 * @return unsigned long That represents the number of days since year 0
	 * @see long operator-()
	 */
	unsigned long date2days() const;
public:
	/**
	 * @brief Construct a new Date object
	 * Empty constructor that initializes the date to year 0, month 1, day 1
	 * 
	 */
	Date();
	/**
	 * @brief Construct a new Date object
	 * May throw exception if there are invalid parameters
	 * 
	 * @param day Unsigned int that initializes the day Private Member
	 * @param month Unsigned int that initializes the month Private Member
	 * @param year Unsigned int that initializes the year Private Member
	 * @throw InvalidMonth() If month is bigger than 12
	 * @throw InvalidDay() If day is bigger than the days in the specified month
	 */
	Date(unsigned int day, unsigned int month, unsigned int year);
	/**
	 * @brief Construct a new Date object
	 * Allows to initialize a Date object with other Date
	 * 
	 * @param date Date with which we want to initialize the new Date object
	 */
	Date(const Date & date);

	Date(std::string &date);

	/**
	 * @brief Get the Day Private Member
	 * 
	 * @return unsigned Retruns the day Private Member
	 */
	unsigned getDay() const { return day; };
	/**
	 * @brief Get the Month Private Member
	 * 
	 * @return unsigned Return the month Private Member
	 */
	unsigned getMonth() const { return month; };
	/**
	 * @brief Get the Year Private Member
	 * 
	 * @return unsigned Return the year Private Member
	 */
	unsigned getYear() const { return year; };

	/**
	 * @brief Set the Day Private Member
	 * May throw exception if the parameter is invalid
	 * 
	 * @param day Unsigned int to be set to the day Private Member
	 * @throw InvalidDay() If day is bigger than the days in the month of the Date Object
	 */
	void setDay(unsigned int day);
	/**
	 * @brief Set the Month Private Member
	 * May throw exception if the parameter is invalid
	 * 
	 * @param month Unsigned int to be set to the month Private Member
	 * @throw InvalidMonth() If month is bigger than 12 or Date Object has more days than the parameter month
	 * @see daysInMonth()
	 */
	void setMonth(unsigned int month);
	/**
	 * @brief Set the Year Private Member
	 * May throw exception if the parameter is invalid
	 * 
	 * @param year Unsigned int to be set to the year Private Member
	 * @throw InvalidYear() If previous year was leap year and this is not or the other way around
	 * @see daysInMonth()
	 */
	void setYear(unsigned int year);

	/**
	 * @brief Overload of the plus operator in order to add a number of days to a date
	 * May call the symmetric operator if the number of days is negative
	 * 
	 * @param days Number of days that you wish to add to the current date
	 * @return Date Returns the final Date after adding all the days
	 * @see dayNumber()
	 * @see daysInYear()
	 * @see daysInMonth()
	 * @see operator-()
	 */
	Date operator+(int days) const;
	/**
	 * @brief Overload of the minus operator in order to remove a number of days of a date
	 * May call the symmetric operator if the number of days is negative
	 * 
	 * @param days Number of days that you wish to remove of the current date
	 * @return Date Returns the final Date after removing all the days
	 * @see dayNumber()
	 * @see daysInYear()
	 * @see daysInMonth()
	 * @see operator+()
	 */
	Date operator-(int days) const;
	/**
	 * @brief Difference in days between to dates
	 * 
	 * @param date Date that you want to remove from the current one to see how many days they differ
	 * @return long Returns the number of days betwwen one date and other
	 * @see date2days()
	 */
	long operator-(const Date & date) const;

	/**
	 * @brief Overload of the equal to operator
	 * 
	 * @param d2 Date with which we are comparing the other Date
	 * @return true If they are the same Date
	 * @return false If the Dates are different
	 */
	bool operator==(const Date& d2) const;
	/**
	 * @brief Overload of the less than operator
	 * 
	 * @param d2 Date with which we are comparing the other Date
	 * @return true If the date in the parameter is greater than the other date
	 * @return false If the date in the parameter is smaller or equal to the other date
	 */
	bool operator<(const Date& d2) const;
	/**
	 * @brief Overload  of the less or equal operator
	 * 
	 * @param d2 Date with which we are comparing the other Date
	 * @return true If the date in the parameter is greater or equal to the other date
	 * @return false If the date in the parameter is smaller than the other date
	 */
	bool operator<=(const Date& d2) const;

	/**
	 * @brief Overload insertion operator to output formated Date
	 * Outputs the date in the DD/MM/year format, where both day and month should have two digits
	 * 
	 * @param os Output stream object where characters are inserted
	 * @param date Formated Date to insert/output
	 * @return ostream& The ostream object (os) passed as parameter
	 */
	friend std::ostream& operator<<(std::ostream &os, const Date & date);
	/**
	 * @brief Overload extraction operator to get a formated Date
	 * Date should be in day-month-year form and the characters separating the numbers should be the same
	 * Date should also be valid
	 * 
	 * @param is Input stream object from which characters are extracted
	 * @param date Formated Date to be extracted
	 * @return istream& The istream object (is) passed as parameter
	 * @throw InvalidDateFormat()
	 * @see Date(d, m, y)
	 */
	friend std::istream& operator>>(std::istream &is, Date & date);

	/**
	 * @brief Get the Current Date object
	 * 
	 * @return Date Returns the Actual Current Date
	 */
	static Date getCurrentDate();

};

/** @} */

#endif
