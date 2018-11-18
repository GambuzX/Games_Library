#ifndef UPDATE_H
#define UPDATE_H

#include "Date.h"
#include <string>

/** @defgroup Update Update Class
 * @{
 *
 * Update Class representing the update of a Home Game
 * Each object has a date of the update, description of the changes and a version number
 * Doing an Update costs 1€ for the User and to play a Game it is required its last version
 * 
 * @see HomeTitle
 * @see Date
 */
class Update {

private:
	Date date; /**< @brief Date of the Update */
	std::string description; /**< @brief Description of the Changes that come with the Update */
	double version; /**< @brief Number of the Version of the Update */
public:
	/**
	 * @brief Construct a new Update object
	 * Empty constructor initializes date to the default date, description to an empty string and version to 0.0
	 * 
	 */
	Update() { date = Date(); description = ""; version = 0.0; };
	/**
	 * @brief Construct a new Update object
	 * Contructor with the release date, which initializes the date to its release
	 * Description will be a string saying "First version" and the Version Number will be the first one (1.0)
	 * 
	 * @param d Release Date to Initialize the date Private Member
	 */
	Update(Date d) { date = d; description = "First version"; version = 1.0; };
	/**
	 * @brief Construct a new Update object
	 * 
	 * @param d Date that initializes the date Private Member
	 * @param desc String that initializes the description Private Member
	 * @param v Double to initialize the version Private Member
	 */
	Update(Date d, std::string desc, double v);

	/**
	 * @brief Get the Date object
	 * 
	 * @return Date Returns Date object
	 */
	Date getDate() const;
	/**
	 * @brief Get the Description Private Member
	 * 
	 * @return string Returns the description Private Member
	 */
	std::string getDescription() const;
	/**
	 * @brief Get the Version Private Member
	 * 
	 * @return double Returns the version Private Member
	 */
	double getVersion() const;

	/**
	 * @brief Overload of the equal to operator
	 * 
	 * @param update Update with which we are comparing the Current Update
	 * @return true If the Update version numbers are the same
	 * @return false If the Update version numbers are different
	 */
	bool operator==(const Update & update) const;
	/**
	 * @brief Overload of less than operator
	 * One Update is "less" than other if its version number is smaller thant the other
	 * 
	 * @param update Update with which we are comparing the Current Update
	 * @return true If the Update version number of the Current Update is less than the one passed as a parameter
	 * @return false If the Update Version number of the Current Update is greater or equal to the parameter one
	 */
	bool operator<(const Update & update) const;
};

/** @} */

#endif
