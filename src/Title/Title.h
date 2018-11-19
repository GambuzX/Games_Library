#ifndef TITLE_H
#define TITLE_H

#include <string>
#include <vector>
#include "Subscription.h"
#include "..\GameLibraryInfo.h"
#include "..\User\User.h"
#include "..\Utilities\Date.h"
#include "..\Utilities\Sale.h"
#include "..\Utilities\Update.h"

// TODO: tentar evitar inclusao de bibliotecas circular (??) para ja esta isto
class User;

/** @defgroup Title Title
 * @{
 *
 * Title Class is the abstract base class for the Home Title and Online Title Classes
 * All the Titles are included in the GamesLibrary
 * Also uses the Date Class to save the release Date and the Sales to keep track of the price history
 * 
 * @see GamesLibrary
 * @see Date
 * @see Sale
 * @see User
 */

/**
 * @brief Age Range Struct to Save the minimun and the maximum recommended age of a Game
 * 
 */
struct ageRange {
	int minAge;	/*!< Minimum Recommended Age */
	int maxAge;	/*!< Maximum Recommended Age */
};

class Title {

private:
	static unsigned int nextTitleID; /**< @brief Static Unsigned int used to assign different IDs to each Title */
	const unsigned int titleID; /**< @brief Unsigned int with the Title ID */
	std::string name; /**< @brief Name of the title */
	double basePrice; /**< @brief Base Price of the title */
	const Date releaseDate; /**< @brief Release Date of the title */
	ageRange ageR;  /**< @brief Age Range recommended for the title */
	gameLibraryPlatform platform; /**< @brief String with the name of the plataform where the Title should be played */
	gameLibraryGenre genre; /**< @brief String with the genre of the Title */
	std::string company; /**< @brief String with the company name that produced the Title */
	std::vector<Sale> pricesHistory; /**< @brief Vector of Sales to keep track of the Title current, passed and possible future sales. Sorted by beginning date */

public:
	/**
	 * @brief Construct a new Title object
	 * Uses the nextTitleID static unsigned int to assign the titleID
	 * 
	 * @param name String that initializes the name Private Member
	 * @param price Double that initializes the basePrice Private Member
	 * @param releaseDate Date that initializes the releaseDate Private constant Member
	 * @param ageR ageRange struct that initializes the ageR Private Member
	 * @param platform String that initializes the platform Private Member
	 * @param genre String that initializes the genre Private Member
	 * @param company String that initializes the company Private Member
	 */
	Title(std::string name, double price, Date releaseDate, ageRange ageR, gameLibraryPlatform platform, gameLibraryGenre genre, std::string company);

	/**
	 * @brief Get the Vector of Updates
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return const vector<Update>& Returns a vector with the title Updates
	 * @throw NotHomeTitle() If it is called on a Online Title Object
	 */
	virtual const std::vector<Update> & getUpdates() const = 0;

	/**
	 * @brief Get the Stats of a Title (hours played)
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return double Returns the number of hours that an Online Title has been played
	 * @throw NotOnlineTitle If it is called on a Home Title Object
	 */
	virtual double getStats() const = 0;

	/**
	 * @brief Get the Number of Users that have the Title
	 * 
	 * @return unsigned int Returns the number of Users that have the Title
	 */
	virtual unsigned int getNumberUsers() const = 0;

	/**
	 * @brief Updates a Home Title
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * Also Throws exception if the parameter is not a new Update
	 * 
	 * @param newUpdate Update that we wish to make to the Home Title
	 * @throw NotHomeTitle() If it is called on a Online Title Object
	 * @throw OldUpdate() If the Update that we are trying to add is already passed
	 */
	virtual void updateTitle(Update * newUpdate) = 0;

	/**
	 * @brief Function that helps to add a new User to the list of owners of that Title
	 * Virtual function that may throw exceptions if User already has the Title
	 * 
	 * @param u User to be added to the list of owners of the Title
	 * @throw DuplicatetUser() If the user already has the Title
	 */
	//TODO: & ou *??
	virtual void addNewUser(User & u) = 0;

	/**
	 * @brief Function that Updates the User Home Title Version to the latest
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * May also throw other exceptions
	 * 
	 * @param usr User that you want to update the copy of the Home Title of
	 * @throw NotHomeTitle() If it is called on a Online Title Object
	 * @throw InexistentUser() If the user specified doesn't own the game
	 * @throw TitleUpToDate() If the Title is already up to date
	 */
	virtual void updateUserVersion(const User & usr) = 0;

	/**
	* @brief Get the total time played of Title by User
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @param usr Pointer to the User to get time played
	* @throw NotOnlineTitle() If it is called on a Home Title Object
	* @throw InexistentUser() If the user specified doesn't own the game
	*/
	virtual double getTimePlayed(const User * usr) const = 0;

	/**
	 * @brief Get the Subscription object
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return Subscription* Return the subscription Private object Member
	 * @throw NotOnlineTitle If it is called on a Home Title Object
	 */
	virtual Subscription * getSubscription() const = 0;

	/**
	 * @brief Get the Name Private Member
	 * 
	 * @return string Return the name Private Member
	 */
	std::string getName() const { return name; };

	/**
	 * @brief Get the Title ID Private Member
	 * 
	 * @return unsigned int Return the titleID Private Member
	 */
	unsigned int getTitleID() const { return titleID; };

	/**
	 * @brief Get the Base Price Private Member
	 * 
	 * @return double Return the basePrice Private Member
	 */
	double getBasePrice() const { return basePrice; };

	/**
	 * @brief Get the Release Date object
	 * 
	 * @return Date Return the releaseDate object
	 */
	Date getReleaseDate() const { return releaseDate; };

	/**
	 * @brief Get the Age Range Private Struct Member
	 * 
	 * @return ageRange Return the ageR Private Struct Member
	 */
	ageRange getAgeRange() const { return ageR; };

	/**
	 * @brief Get the Platform Private Member
	 * 
	 * @return gameLibraryPlatform Return the platform Private Member
	 */
	gameLibraryPlatform getPlatform() const { return platform; };

	/**
	 * @brief Get the Genre Private Member
	 * 
	 * @return gameLibraryGenre Return the genre Private Member 
	 */
	gameLibraryGenre getGenre() const { return genre; };

	/**
	 * @brief Get the Company Private Member
	 * 
	 * @return string Return the company Private Member 
	 */
	std::string getCompany() const { return company; };

	/**
	 * @brief Get the Last Sale object
	 * May throw some exceptions if there are no sales
	 * 
	 * @return const Sale& Return the Last Sale from the pricesHistory Vector
	 * @throw InexistentSale() If there are no Sales
	 */
	const Sale & getLastSale() const;

	/**
	 * @brief Get the Current Price object
	 * 
	 * @param date Date for which we want to calculate the "Current" price
	 * @return double Return the basePrice if there is no sale Active, or the Price decreased by the Sale factor otherwise
	 */
	double getCurrentPrice(Date & date) const;

	// TODO: Acho que set's neste faz sentido pq j� tem cenas associadas (podes s� querer mudar plat, gen ou emp a n�o ser que const)
	/**
	 * @brief Add new Promotion to the vector of Sales
	 * May throw some exceptions if the promotions overlap or the "new" one is old
	 * This function also keeps the priceHistory vector in chronological order of the beginning date
	 * 
	 * @param promotion 
	 * @throw ExpiredSale() If the promotion we are trying to add has already expired
	 * @throw OverlappingSales() If the promotion overlaps one already planned
	 */
	void addPromotion(Sale & promotion);

	/**
	 * @brief Remove future Promotion off of the vector of Sales
	 * May throw some exceptions if the promotion has already started or doesn't exists
	 * 
	 * @param saleBeginning Date when the promotion that we want to Remove begins
	 * @throw SaleStarted() If the sale already has started or passed
	 * @throw InexistentSale() If doesn't exist a sale beginning on that date
	 */
	void removePromotion(Date & saleBeginning);

	/**
	 * @brief Overload of the less than operator
	 * Allows comparing to titles by titleID number
	 * 
	 * @param t2 Title with which we are comparing the "first" Title
	 * @return true If the title on the left of signal has a smaller titleID
	 * @return false If the title on the left of signal has a bigger or equal titleID to the one on the right side
	 */
	bool operator<(const Title & t2) const;
};

/** @} */

#endif
