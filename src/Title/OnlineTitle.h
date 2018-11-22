#ifndef ONLINETITLE_H
#define ONLINETITLE_H

#include <map>
#include <vector>
#include "..\Utilities\Exceptions.h"
#include "..\Utilities\CompareObj.h"
#include "Title.h"

/** @defgroup Title Online Title
 * @{
 *
 * Online Title Class is a derived class of the Title Class
 * Allows Title to keep track of the User Sessions to calculate the Stats and Saves the type of Subscription
 * 
 * @see Title
 * @see Subscription
 * @see Session
 * @see User
 */
class OnlineTitle : public Title {

private:
	Subscription* subscription; /**< @brief Subscription pointer to the type of subscription used (Fixed or Dynamic) */
	std::map<User*, std::vector<Session>, ComparePtr<User>> titleStats; /**< @brief Map of User to their vector of ordered sessions */

public:
	/**
	 * @brief Construct a new Online Title object
	 * Calls the Title Contructor and initializes the Subscription
	 * 
	 * @param name String that initializes the name Private Member
	 * @param price Double that initializes the basePrice Private Member
	 * @param releaseDate Date that initializes the releaseDate Private constant Member
	 * @param ageR ageRange struct that initializes the ageR Private Member
	 * @param platform gameLibraryPlatform that initializes the platform Private Member
	 * @param genre gameLibraryGenre that initializes the genre Private Member
	 * @param company String that initializes the company Private Member
	 * @param subs Subscription that initializes the subscription Private Member
	 */
	OnlineTitle(std::string name, double price, Date releaseDate, ageRange ageR, gameLibraryPlatform platform, gameLibraryGenre genre, std::string company, Subscription* subs);
	
	/**
	 * @brief Get the Subscription object
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return Subscription* Return the subscription Private object Member
	 * @throw NotOnlineTitle If it is called on a Home Title Object
	 */
	Subscription * getSubscription() const override
    { return subscription; };

	/**
	 * @brief Get the Vector of Updates
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return const vector<Update>& Returns a vector with the title Updates
	 * @throw NotHomeTitle() If it is called on a Online Title Object
	 */
	const std::vector<Update> & getUpdates() const override;

	/**
	 * @brief Get the Number Users
	 * 
	 * @return unsigned int Returns the number of Users that have the Title
	 */
	unsigned int getNumberUsers() const override { return titleStats.size(); };

	/**
	 * @brief Get the Number of Users within an Age Range that have the Title
	 *
	 * @param Age range Users must belong to
	 * @return unsigned int Returns the number of Users that have the Title
	 */
	unsigned int getNumberUsers(ageRange ageR) const override;

	/**
	 * @brief Get the Stats of a Title (hours played)
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return double Returns the number of hours that an Online Title has been played
	 * @throw NotOnlineTitle If it is called on a Home Title Object
	 */
	double getStats() const override;

	/**
	 * @brief Get the Stats of a Title of a certain User (hours played)
	 * May also throw other exceptions if the user is not a owner of the Title
	 * 
	 * @param u User that you want to know the amount of time (in hours) that he played the Online Game
	 * @return double Returns the number of hours that an Online Title has been played by a certain User
	 * @throw InexistentUser() If the user specified doesn't own the Online Title
	 */
	double getStats(const User * u) const;

	/**
	 * @brief Get the Stats of a Title of a certain User (hours played)
	 * May also throw other exceptions if the user is not a owner of the Title
	 * 
	 * @param userID ID of the user that you want to know the amount of time (in hours) that he played the Online Game
	 * @return double Returns the number of hours that an Online Title has been played by a certain User identifie
	 * @throw InexistentUser() If the user specified by its ID doesn't own the Online Title
	 */
	double getStats(unsigned int userID) const;

	//const std::map<User*, std::vector<Session>, ComparePtr<User>> & getLastNSessions(unsigned int n) const;

	/**
	 * @brief Updates a Home Title
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * Also Throws exception if the parameter is not a new Update
	 * 
	 * @param newUpdate Update that we wish to make to the Home Title
	 * @throw NotHomeTitle() If it is called on a Online Title Object
	 * @throw OldUpdate() If the Update that we are trying to add is already passed
	 */
	void updateTitle(Update * newUpdate) override;

	/**
	* @brief Function that verifies if a User needs an Update
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @param usr User that you want to check if needs an Update
	* @throw NotHomeTitle() If it is called on a Online Title Object
	* @throw InexistentUser() If the user specified doesn't own the game
	*/
	bool userNeedsUpdate(User * usr) const override { throw NotHomeTitle(getTitleID()); };
	
	/**
	* @brief Get the Current Update Version object
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @return const Update& Return the Last Update made to the Home Title
	* @throw NotHomeTitle() If it is called on a Online Title Object
	*/
	const Update & getCurrentVersion() const override
    { throw NotHomeTitle(getTitleID()); };

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
	void updateUserVersion(const User * usr) override;

	/**
	 * @brief Function that helps to add a new User to the list of owners of that Title
	 * Virtual function that may throw exceptions if User already has the Title
	 * 
	 * @param u User to be added to the list of owners of the Title
	 * @throw DuplicatetUser() If the user already has the Title
	 */
	void addNewUser(User * u) override;

	/**
	* @brief Get the total time played of Title by User
	* Virtual function that may throw exceptions if called on the incorrect object
	*
	* @param usr Pointer to the User to get time played
	* @throw NotOnlineTitle() If it is called on a Home Title Object
	* @throw InexistentUser() If the user specified doesn't own the game
	*/
	double getTimePlayed(const User * usr) const override { return getStats(usr); }

	/**
	 * @brief Adds a new Session to the User's vector of sessions kepping it in order
	 * May also throw other exceptions if the user is not a owner of the Title
	 * 
	 * @param u User that you want to add a session to
	 * @param sess Session to be added to the Vector of Sessions
	 * @throw InexistentUser() If the user specified by its ID doesn't own the Home Title
	 */
	void addNewSession(const User * u, const Session & sess) override;

	/**
	 * @brief Adds a new Session to the User's vector of sessions kepping it in order
	 * May also throw other exceptions if the user is not a owner of the Title
	 * 
	 * @param userID ID of the User that you want to add a session to
	 * @param sess Session to be added to the Vector of Sessions
	 * @throw InexistentUser() If the user specified by its ID doesn't own the Home Title
	 */
	void addNewSession(unsigned int userID, const Session & sess);

	void displayTitleInfo(std::ostream& os) override;
	//bool operator<(const Title & t2) const override;

};

/** @} */

#endif
