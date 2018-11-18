#ifndef HOMETITLE_H
#define HOMETITLE_H

#include <sstream>
#include <map>
#include "Title.h"
#include "..\Utilities\Exceptions.h"
#include "..\Utilities\CompareObj.h"

/** @defgroup Title Home Title
 * @{
 *
 * Home Title Class is a derived class of the Title Class
 * Allows Home Title to keep track of its update history and the one of each user
 * 
 * @see Title
 * @see Update
 * @see User
 */
class HomeTitle : public Title {

private:
	std::vector<Update> titleUpdateHistory; /**< @brief Vector of Updates to keep track of the update history of the home title */
	std::map<User*, std::vector<Update*>, ComparePtr<User>> userUpdates; /**< @brief Map of User to their update history */

public:
	/**
	 * @brief Construct a new Home Title object
	 * Calls the Title Contructor and initializes the Update History vector with the Update 1.0 (first Update that you already have when you buy the game)
	 * 
	 * @param name String that initializes the name Private Member
	 * @param price Double that initializes the basePrice Private Member
	 * @param releaseDate Date that initializes the releaseDate Private constant Member and the Update in the titleUpdateHistory Vector
	 * @param ageR ageRange struct that initializes the ageR Private Member
	 * @param platform String that initializes the platform Private Member
	 * @param genre String that initializes the genre Private Member
	 * @param company String that initializes the company Private Member
	 * @see Update(Date)
	 */
	HomeTitle(std::string name, double price, Date releaseDate, ageRange ageR, std::string platform, std::string genre, std::string company);
	
	/**
	 * @brief Function that helps to add a new User to the list of owners of that Title
	 * Virtual function that may throw exceptions if User already has the Title
	 * 
	 * @param u User to be added to the list of owners of the Title
	 * @throw DuplicatetUser() If the user already has the Title
	 */
	void addNewUser(User & u) override;

	/**
	 * @brief Get the Vector of Updates
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return const vector<Update>& Returns a vector with the title Updates
	 * @throw NotHomeTitle() If it is called on a Online Title Object
	 */
	const std::vector<Update> & getUpdates() const override { return titleUpdateHistory; };
	/**
	 * @brief Get the Number Users
	 * 
	 * @return unsigned int Returns the number of Users that have the Title
	 */
	unsigned int getNumberUsers() const override { return userUpdates.size(); };
	/**
	 * @brief Get the Stats of a Title (hours played)
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return double Returns the number of hours that an Online Title has been played
	 * @throw NotOnlineTitle If it is called on a Home Title Object
	 */
	double getStats() const override;
	/**
	 * @brief Get the Subscription object
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * 
	 * @return const Subscription* Return the subscription Private object Member
	 * @throw NotOnlineTitle If it is called on a Home Title Object
	 */
	Subscription * getSubscription() const { throw NotOnlineTitle(getTitleID()); };

	/**
	 * @brief Get the Current Update Version object
	 * 
	 * @return const Update& Return the Last Update made to the Home Title
	 */
	const Update & getCurrentVersion() const { return titleUpdateHistory.at(titleUpdateHistory.size() - 1); };
	/**
	 * @brief Get the Current User Update Version object
	 * May also throw other exceptions if the user is not a owner of the Title
	 * 
	 * @param u User that you want to know the last update/Current Version of his Home Title of
	 * @return const Update& Return the Last Update made by the User
	 * @throw InexistentUser() If the user specified doesn't own the Home Title
	 */
	const Update & getCurrentUserVersion(const User & u) const;
	/**
	 * @brief Get the Current User Update Version object
	 * May also throw other exceptions if the user is not a owner of the Title
	 * 
	 * @param userID ID of the user that you want to know the last update of/Current Version of his Home Title
	 * @return const Update& Return the Last Update made by the User
	 * @throw InexistentUser() If the user specified by its ID doesn't own the Home Title
	 */
	const Update & getCurrentUserVersion(unsigned int userID) const;
	//const Update & getCurrentUserVersion(std::string name) const;

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
	 * @brief Function that Updates the User Home Title Version to the latest
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * May also throw other exceptions
	 * 
	 * @param usr User that you want to update the copy of the Home Title of
	 * @throw NotHomeTitle() If it is called on a Online Title Object
	 * @throw InexistentUser() If the user specified doesn't own the game
	 * @throw TitleUpToDate() If the Title is already up to date
	 */
	void updateUserVersion(const User & usr) override;
	/**
	 * @brief Function that Updates the User Home Title Version to the latest
	 * Virtual function that may throw exceptions if called on the incorrect object
	 * May also throw other exceptions
	 * 
	 * @param userID ID of the user that you want to update the copy of the Home Title of
	 * @throw NotHomeTitle() If it is called on a Online Title Object
	 * @throw InexistentUser() If the user specified doesn't own the game
	 * @throw TitleUpToDate() If the Title is already up to date
	 */
	void updateUserVersion(unsigned int userID);
	//void updateUserVersion(std::string name);

	//bool operator<(const Title & t2) const override;

};

/** @} */

#endif
