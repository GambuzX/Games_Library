#ifndef TITLE_H
#define TITLE_H

#include <string>
#include <map>
#include <vector>
#include "Subscription.h"
#include "..\GameLibraryInfo.h"
#include "..\User\User.h"
#include "..\Utilities\Date.h"
#include "..\Utilities\Sale.h"
#include "..\Utilities\Update.h"
#include "..\Utilities\Session.h"
#include "..\Utilities\CompareObj.h"

// TODO: tentar evitar inclusao de bibliotecas circular (??) para ja esta isto
class User;

/** @defgroup Title Titles
 * @ingroup GameLibrary
 * @{
 *
 * @brief  Group holding all the information about Titles and related classes.
 *
 * This group contains the base class Title and its derived classes HomeTitle and OnlineTitle. The other classes included are
 * structures that were needed to implement all the functionalities related to the titles.
 * 
 * 
 * @see Title
 * @see HomeTitle
 * @see OnlineTitle
 * @see Sale
 * @see Update
 * @see Subscription
 * @see Session
 */

/**
 * @brief Age Range Struct to save the minimum and the maximum recommended age of a Game
 */
struct ageRange {
	int minAge;	/*!< Minimum Recommended Age */
	int maxAge;	/*!< Maximum Recommended Age */
};

/**
* @brief Abstract class that represents a Title in the Game Library.
*
*/
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
	// TODO: ver isto
	float minimumBuyProbability; /**< @brief Float with the minimum Buy Probability so that a User is considered asleep/a potencial buyer*/

public:
	/**
	 * @brief Construct a new Title object
	 * Uses the nextTitleID static unsigned int to assign the titleID
	 * Defaults minimumBuyProbability to 0
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
	 * @brief Set the Minimum Buy Probability Private Member
	 * May throw exception if the parameter is invalid
	 *
	 * @param minimumBuyProb float to be set to the minimumBuyProbability Private Member
	 * @throw InvalidProbability() If minimumBuyProb is not less or equal to 1 and greater or equal to 0
	 */
	void setMinimumBuyProbability(float minimumBuyProb);

	/**
	 * @brief Get the  Minimum Buy Probability Private Member
	 *
	 * @return const float Returns the minimumBuyProbability Private Member
	 */
	const float getMinimumBuyProbability() { return minimumBuyProbability; };

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
	 * @brief Get the Number of Users within an Age Range that have the Title
	 *
	 * @param Age range Users must belong to
	 * @return unsigned int Returns the number of Users that have the Title
	 */
	virtual unsigned int getNumberUsers(ageRange ageR) const = 0;

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
	* @brief Reset the vector of updates
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @throw NotHomeTitle() If it is called on a Online Title Object
	*/
	virtual void resetUpdates() = 0;

	/**
	 * @brief Function that helps to add a new User to the list of owners of that Title
	 * Virtual function that may throw exceptions if User already has the Title
	 * 
	 * @param u User to be added to the list of owners of the Title
	 * @throw DuplicatetUser() If the user already has the Title
	 */
	virtual void addNewUser(User * u) = 0;

	/**
	* @brief Function that verifies if a User needs an Update
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @param usr User that you want to check if needs an Update
	* @throw NotHomeTitle() If it is called on a Online Title Object
	* @throw InexistentUser() If the user specified doesn't own the game
	*/
	virtual bool userNeedsUpdate(User * usr) const = 0;

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
	virtual void updateUserVersion(const User * usr) = 0;

	/**
	 * @brief Adds a new Session to the User's vector of sessions kepping it in order
	 * May also throw other exceptions if the user is not a owner of the Title
	 *
	 * @param u User that you want to add a session to
	 * @param sess Session to be added to the Vector of Sessions
	 * @throw InexistentUser() If the user specified by its ID doesn't own the Home Title
	 * @throw NotOnlineTitle If it is called on a Home Title Object
	 */
	virtual void addNewSession(const User * u, const Session & sess) = 0;

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
	* @brief Get the Current Update Version object
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @return const Update& Return the Last Update made to the Home Title
	* @throw NotHomeTitle() If it is called on a Online Title Object
	*/
	virtual const Update & getCurrentVersion() const = 0;

	/**
	* @brief Get the last N Sessions of a User for this Title
	* Virtual function that may throw exceptions if called on the incorrect object
	* May also throw other exceptions if the user is not a owner of the Title
	*
	* @param usr Pointer to the User
	* @param n Number of sessions to get
	* @return vector<Session> Containing the last N sessions of User
	* @throw InexistentUser() If the user specified by its ID doesn't own the Online Title
	* @throw NotOnlineTitle If it is called on a Home Title Object
	*/
	virtual const std::vector<Session> getLastNUserSessions(User * usr, int n) const = 0;

	/**
	* @brief Get Top 3 Players Session
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @return const map<User*, const std::vector<Session>*, ComparePtr<User> Containing all the sessions of the top 3 users
	* @throw NotOnlineTitle If it is called on a Home Title Object
	*/
	virtual const std::map<User*, const std::vector<Session>*, ComparePtr<User>> getTop3PlayersSessions() const = 0;

	/**
	* @brief Get the last N Sessions of all Users for this Title
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @param n Number of sessions to get per User
	* @return map<User*, vector<Session>, ComparePtr<User>> Containing the last N sessions of all Users
	* @throw NotOnlineTitle If it is called on a Home Title Object
	*/
	virtual const std::map<User*, std::vector<Session>, ComparePtr<User>> getAllUsersLastNSessions(unsigned int n) const = 0;

	/**
	* @brief Get the Title Sessions object
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @return const std::map<User*, std::vector<Session>, ComparePtr<User>> * Returns Pointer to the titleStats Private Member
	* @throw NotOnlineTitle If it is called on a Home Title Object
	*/
	virtual const std::map<User*, std::vector<Session>, ComparePtr<User>> * getTitleSessions() const = 0;

	virtual void displayTitleInfo(std::ostream &os);

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
	 * @brief Get the Platform Name of the Private Member
	 * 
	 * @return std::string Returns the conversion of the enum gameLibraryPlatform to a string
	 * @see platformEnum2string()
	 */
	std::string getPlatformName() const { return platformEnum2string(platform); };
	
	/**
	 * @brief Get the Genre Private Member
	 * 
	 * @return gameLibraryGenre Return the genre Private Member 
	 */
	gameLibraryGenre getGenre() const { return genre; };

	/**
	 * @brief Get the Genre Name of the Private Member
	 * 
	 * @return std::string Returns the conversion of the enum gameLibraryGenre to a string
	 * @see genreEnum2string()
	 */
	std::string getGenreName() const { return genreEnum2string(genre); };
	
	/**
	 * @brief Get the Company Private Member
	 * 
	 * @return string Return the company Private Member 
	 */
	std::string getCompany() const { return company; };

	/**
	* @brief Get the Sale History Private Member
	*
	* @return const std::vector<Sale>& Return the pricesHistory Vector Private Member
	*/
	const std::vector<Sale> & getSaleHistory() const{ return pricesHistory; };

	/**
	 * @brief Get the Last Sale object
	 * May throw some exceptions if there are no sales
	 * 
	 * @return const Sale& Return the Last Sale from the pricesHistory Vector
	 * @throw InexistentSale() If there are no Sales
	 */
	const Sale & getLastSale() const;

	/**
	* @brief Get the Sale object on specified Date
	* May throw some exceptions if there are no sales
	*
	* @param date Date when we want to know if there is a Sale
	* @return const Sale& Return the Current Sale active on the Date
	* @throw InexistentSale() If there are no Sales
	*/
	const Sale & getSaleOn(Date & date) const;

	/**
	 * @brief Get the Current Price object
	 * 
	 * @param date Date for which we want to calculate the "Current" price
	 * @return double Return the basePrice if there is no sale Active, or the Price decreased by the Sale factor otherwise
	 */
	double getCurrentPrice(Date & date) const;

	/**
	 * @brief Add new Promotion to the vector of Sales
	 * May throw some exceptions if the promotions overlap or the "new" one is old
	 * This function also keeps the priceHistory vector in chronological order of the beginning date
	 * 
	 * @param promotion 
	 * @throw ExpiredSale() If the promotion we are trying to add has already expired
	 * @throw OverlappingSales() If the promotion overlaps one already planned
	 */
	void addPromotion(Sale promotion);

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

	friend std::ostream& operator<<(std::ostream &os, const Title &title);
	
};

/** @} */

#endif
