#ifndef WISHLIST_ENTRY_H
#define WISHLIST_ENTRY_H

#include "..\Title\Title.h"

class Title;

/** @addtogroup UserUtility
* @{
*/

/**
* @brief Class representing a Wishlist Entry
*/
class WishlistEntry {
private:
	unsigned interest; /**< @brief Unsigned with the entry interest, from 1 to 10 */
	float buyChance; /**< @brief Float with the user buy chance for the Title, between 0 and 1 */
	Title * title; /**< @brief Title * pointing to the Title in the wishlist */

public:

	/**
	* @brief Construct a new WishlistEntry object
	* Assures interest and buyChance are whitin acceptable ranges
	*
	* @param interest Interest in this title, from 1 to 10
	* @param buyChance Chance of the user buying this title, from 0 to 1
	* @param title Pointer to the Title the user wants
	*/
	WishlistEntry(unsigned interest, float buyChance, Title* title);
	
	/**
	* @brief Get the interest Private Member
	*
	* @return unsigned Returns the interest Private Member
	*/
	unsigned getInterest() const { return interest; }

	/**
	* @brief Get the buyChance Private Member
	*
	* @return float Returns the buyChance Private Member
	*/
	float getBuyChance() const { return buyChance; }

	/**
	* @brief Get the title Private Member
	*
	* @return Title * Returns the title Private Member
	*/
	Title * getTitle() const { return title;  }

	/**
	* @brief Set the interest Private Member
	*
	* @param New value for the interest Private Member
	*/
	void setInterest(unsigned interest);

	/**
	* @brief Set the buyChance Private Member
	*
	* @param New value for buyChance Private Member
	*/
	void setBuyChance(float buyChance);

	/**
	* @brief Compares two WishlistEntry objects
	* Organized by interest and, if equal, by buyChance
	*
	* @param ref WishlistEntry to compare with
	* @return bool representing if one WishlistEntry has less priority than the other
	*/
	bool operator<(const WishlistEntry &ref) const;
};

/** @} */

#endif
