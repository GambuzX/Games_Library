#ifndef SALE_H
#define SALE_H

#include "Date.h"

/** @defgroup TitleUtility Titles Utility
* @ingroup Title
* @{
*
* @brief Group holding the classes required to implement Title and its derived classes
*
* Utility classes related to the GameLibrary Titles, HomeTitles and OnlineTitles
*
* @see Title
* @see HomeTitle
* @see OnlineTitle
*/

 /**
 * @brief Class representing a promotion of a Title
 */
class Sale {

private:
	Date startDate; /**< @brief Starting Date of the Sale */
	Date endDate; /**< @brief Ending Date of the Sale */
	double saleFactor; /**< @brief Factor by which the original Title price will decrease */
public:
	/**
	 * @brief Construct a new Sale object
	 * 
	 * @param start Date that initializes the startDate Private Member
	 * @param end Date that initializes the endDate Private Member
	 * @param val Double that initializes the saleFactor Private Member
	 */
	Sale(Date start, Date end, double val);

	/**
	 * @brief Get the Start Date object
	 * 
	 * @return Date Returns the startDate object
	 */
	Date getStartDate() const;
	/**
	 * @brief Get the End Date object
	 * 
	 * @return Date Returns the endDate object
	 */
	Date getEndDate() const;
	/**
	 * @brief Get the Sale Factor Private Member
	 * 
	 * @return double Returns the saleFactor Private Member
	 */
	double getSaleFactor() const;

	/**
	 * @brief Verifies if the sale is active during the date passed as parameter
	 * 
	 * @param date Date in which we want know if the sale is Active
	 * @return true If the Sale is Active on the specified date
	 * @return false If the Sale is no longer or not yet Active on that date
	 */
	bool isActiveOn(const Date & date) const;

	/**
	 * @brief Overload of less operator
	 * A Sale is "less" than the other if its beginning date is before the second one
	 * 
	 * @param s2 Sale with which we are comparing the "Current" Sale
	 * @return true  If the "Current" Sale starts before the one passed as paremeter
	 * @return false If the "Current" Sale starts in the same day or after the one passed as paremeter
	 */
	bool operator<(const Sale& s2) const;

	friend std::ostream& operator<<(std::ostream &os, const Sale &s);
};

/** @} */

#endif
