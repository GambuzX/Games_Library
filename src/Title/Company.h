#ifndef COMPANY_H
#define COMPANY_H

#include <set>
#include <string>
#include "Title.h"
#include "..\Utilities\CompareObj.h"

/** @defgroup GameLibraryUtility Game Library Utility
* @ingroup GameLibrary
* @{
*
* @brief Group holding the utility classes required to implement the Game Library class
*
* Utility classes related to the GameLibrary
*
* @see GameLibrary
*/

/**
* @brief typedef for a set of titles
*/
typedef std::set<Title*, ComparePtr<Title>> titleSet;

/**
* @brief Class representing a Company in the Game Library
*/
class Company
{
private:
	titleSet createdTitles; /**< @brief Set of the Titles created by this company */
	std::string name; /**< @brief String with the company name */
	unsigned NIF; /**< @brief unsigned with the company NIF */
	unsigned contact; /**< @brief unsigned with the company contact information */

public:
	/**
	* @brief Construct a new Company object
	*
	* @param n String that initializes the name Private Member
	* @param nif Unsigned that initializes the NIF Private Member
	* @param cont Unsigned that initializes the contact Private Member
	*/
	Company(std::string n, unsigned nif, unsigned cont) : name(n), NIF(nif), contact(cont) {}

	/**
	* @brief Adds a title to the list of the company created titles
	*
	* @param title Pointer to title to add to the createdTitles set
	* @return bool Returns true upon success, false otherwise
	*/
	bool addTitle(Title * title);

	/**
	* @brief Get the name Private Member
	*
	* @return Unsigned Returns the name Private Member
	*/
	std::string getName() { return name;  }

	/**
	* @brief Get the NIF Private Member
	*
	* @return Unsigned Returns the NIF Private Member
	*/
	unsigned getNIF() { return NIF; }

	/**
	* @brief Set the NIF Private Member
	*
	* @param nif New NIF value to set
	*/
	void setNIF(unsigned nif) { NIF = nif; }

	/**
	* @brief Get the contact Private Member
	*
	* @return Unsigned Returns the contact Private Member
	*/
	unsigned getContact() { return contact; }

	/**
	* @brief Set the contact Private Member
	*
	* @param cont New contact value to set
	*/
	void setContact(unsigned cont) { contact = cont; }
	/**
	* @brief Get the createdTitles Private Member
	*
	* @return titleSet Returns the createdTitles Private Member
	*/
	titleSet getTitles() { return createdTitles; }

	/**
	* @brief Get the number of titles in the createdTitles set
	*
	* @return Unsigned Returns the number of titles in the createdTitles Private Member
	*/
	unsigned getNTitles() { return createdTitles.size(); }
};


/**
* @brief Struct for comparing Company Pointer objects
*/
struct CompareCompany
{
	bool operator()(Company * c1,  Company * c2) const
	{
		if (c1->getNTitles() == c2->getNTitles())
			return c1->getName() < c2->getName();
		return c1->getNTitles() < c2->getNTitles();
	}
};


/** @} */

#endif
