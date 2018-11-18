#ifndef SALE_H
#define SALE_H

#include "Date.h"

/** @defgroup Sale Sale Class
 * @{
 *
 * Sale Class representing a promotion of a Title
 * Each object has a starting date for the beginnig of the Sale and an End Date
 * It also has a Sale Factor that will alter the price. 
 * Ex: sale factor = 0.5, price of the game is half of the original during the period that the sale lasts
 * 
 * @see Title
 * @see Date
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
};

/** @} */

#endif
