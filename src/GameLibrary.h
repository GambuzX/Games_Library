#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H

#include <set>
#include <map>
#include <fstream>
#include <unordered_set>
#include "GameLibraryInfo.h"
#include "Title\Title.h"
#include "Title\Company.h"
#include "User\User.h"
#include "Utilities\Date.h"
#include "Utilities\Update.h"
#include "Utilities\CompareObj.h"

/** @defgroup GameLibrary Game Library
* @{
*
* @brief Game Library system to manage Users and Titles
* GameLibrary Class represents a Game Library system to manage Users and Titles.
* This Class has an internal Date to keep track of the time
*
* @see User
* @see Title
*/

// TODO: comentar e passar para compareobj??
struct UserPtrHash
{
	// PARA já djb2 depois se houver tempo mudar faz 33*...
	int operator() (const User * user) const
	{
		unsigned long hash = 5381;
		for (char c : user->getEmail()) {
			if (c != '@')
				hash = (hash << 5) + hash + c;
		}
		return hash;
	}

	bool operator() (const User * user1, const User * user2) const
	{
		return user1->getEmail() == user2->getEmail();
	}
};

typedef std::set<Title*, ComparePtr<Title>> titlesSet;
typedef std::map<Title*, double, ComparePtr<Title>> titlesRevenueMap;
typedef std::map<User*, std::set<Title*, ComparePtr<Title>>, ComparePtr<User>> usersMap;
typedef std::unordered_set<User *, UserPtrHash, UserPtrHash> HashTabUsersPtr;
typedef std::map<Title*, HashTabUsersPtr, ComparePtr<Title>> titleUserHashTabMap;
typedef std::set<Company*, CompareCompany> companiesSet;

/**
 * @brief Class representing the Game Library system
 */
class GameLibrary {
private:
	static titlesSet titles; /**< @brief Static Set of the Game Library Titles */
	static titlesRevenueMap titlesRevenue; /**< @brief Static Map of Titles to their respective total revenue */
	static Date libraryDate;  /**< @brief Date to keep track of the current time */
	static titleUserHashTabMap asleepUsers; /**< @brief Map of Titles to their respective hash tables with the "asleep" Users pointers */

	usersMap users; /**< @brief Map of Users to their respective list of Titles */

	companiesSet platformCompanies; /**< @brief Set of the Companies that exist in this Game Library */

public:
	/**
	* @brief Game Library class Destructor
	* Frees the space allocated for the Users and Titles
	*/
	~GameLibrary();

	/**
	 * @brief Getter method for the set of registered companies
	 * @return set of registered companies
	 */
	companiesSet getCompanies() { return platformCompanies; };

	/**
	* @brief Adds a User to the Game Library
	* Constructs a new user with the given parameters
	* May throw some exceptions if there is already an user with the specified email
	*
	* @param name String that initializes the User's name
	* @param email String that initializes the User's email
	* @param age Int that initializes the User's age
	* @param address Address that initializes the User's address
	* @throw DuplicatedUser() If the email is a duplicate
	*/
	void addUser(std::string name, std::string email, int age, Address address);

	/**
	 * @brief Get the Titles Private Member
	 * 
	 * @return const std::set<Title*, ComparePtr<Title>>& Returns titles Private Member
	 */
	const std::set<Title*, ComparePtr<Title>> & getTitles() const { return titles; };

	/**
	* @brief Get the Users Private Member
	*
	* @return const std::map<User*, std::set<Title*, ComparePtr<Title>>, ComparePtr<User>>& Returns users Private Member
	*/
	const std::map<User*, std::set<Title*, ComparePtr<Title>>, ComparePtr<User>> & getUsers() const { return users; };

	/**
	* @brief Adds a User to the Game Library
	*
	* @param user Pointer to the User to be added
	*/
	void addUser(User * user);

	/**
	* @brief Removes a User from the Game Library
	*
	* @param user Pointer to the User to be removed
	* @return bool Returns true if successfull, false otherwise
	*/
	bool removeUser(User * user);

	/**
	* @brief Get the pointer to a User
	*
	* @param email User email
	* @return User* Returns pointer to User, nullptr if not found
	*/
	User * getUser(std::string email);

	/**
	* @brief Adds a Title to the Game Library
	* Returns false if Title with same name and platform already exists
	*
	* @param user Pointer to the Title to be added
	* @return bool Returns true if successfully added title, false otherwise
	*/
	bool addTitle(Title * title);

	/**
	* @brief Removes a Title from the Game Library
	*
	* @param title Pointer to the Title to be removed
	* @return bool Returns true if successfull, false otherwise
	*/
	bool removeTitle(Title * title);

	/**
	* @brief Removes a Title from the Game Library
	*
	* @param id ID of Title to be removed
	* @return bool Returns true if successfull, false otherwise
	*/
	bool removeTitle(unsigned int id);

	/**
	* @brief Adds a company to the Game Library
	*
	* @param comp Pointer to new company
	* @return bool Returns true if successfull, false otherwise
	*/
	bool addCompany(Company * comp);

	/**
	* @brief Removes a company from the Game Library
	*
	* @param comp Pointer to company to remove
	* @return bool Returns true if successfull, false otherwise
	*/
	bool removeCompany(Company * comp);

	/**
	* @brief Finds a company based on its name
	*
	* @param name Name of the company to find
	* @return Company * Pointer to the company found, nullptr if not found
	*/
	Company * getCompany(std::string name);

	/**
	* @brief Edits a company from the Game Library
	*
	* @param name Name of company to edit
	* @param NIF New NIF for the company
	* @param contact New contact for the company
	* @return bool Returns true if successfull, false otherwise
	*/
	bool editCompany(std::string name, unsigned NIF, unsigned contact);

	/**
	* @brief Adds a title to a company
	*
	* @param companyName Name of company to add a Title
	* @param title Pointer to the title to add
	* @return bool Returns true if successfull, false otherwise
	*/
	bool addTitleToCompany(std::string companyName, Title * title);

	/**
	* Saves the current Game Library and all of its data to 3 different files,
	* one for the games registered in the library, one for the users and their titles
	* and another one for the transactions
	*/
	void saveGameLibrary();

	/**
	* @brief Loads a previously saved Game Library data to the current Game Library instance
	*
	* @param file File to load the data from
	*/
	void loadGameLibrary();

	/**
	* @brief Updates a Title
	* Uses a try catch to verify if the title is a Home Title
	*
	* @param title Home Title to be updated
	* @param update New Update to be added
	* @return bool Returns true if successfull, false otherwise
	*/
	bool updateTitle(Title* title, Update * update);

	/**
	* @brief Verify if a platform is supported by the Game Library
	*
	* @param platform Platform to check validity
	* @return bool Returns true if is supported, false otherwise
	*/
	//bool validPlatform(std::string plat) const;

	/**
	* @brief Builds a popularity ranking of the Game Library Titles
	* Ranking is based on the combination of the 3 parameters provided
	*
	* @param os Output stream to write ranking to
	* @param platform Filter to limit ranking to this platform
	* @param genre Filter to limit ranking to this genre
	* @param ageR Filter to limit ranking to this age group
	*/
	void buildGlobalPopularityRanking(std::ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR);

	/**
	* @brief Builds a revenue ranking of the Game Library Titles
	* Ranking is based on the combination of the 3 parameters provided
	*
	* @param os Output stream to write ranking to
	* @param platform Filter to limit ranking to this platform
	* @param genre Filter to limit ranking to this genre
	* @param ageR Filter to limit ranking to this age group
	*/
	void buildGlobalRevenueRanking(std::ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR);

	/**
	* @brief Builds a ranking based on a User's most played Online Titles
	* Ranking is based on the combination of the platform and genre parameters
	*
	* @param os Output stream to write ranking to
	* @param usr User to get info from
	* @param platform Filter to limit ranking to this platform
	* @param genre Filter to limit ranking to this genre
	*/
	void buildUserMostPlayedTitlesRanking(std::ostream & os, User * usr, gameLibraryPlatform platform, gameLibraryGenre genre);

	/**
	* @brief Returns a set with all the titles that respect a certain criteria
	*
	* @param platform Filter to limit titles to this platform
	* @param genre Filter to limit titles to this genre
	* @param ageR Filter to limit titles to this age range
	* @return Set of pointers to the titles that match
	*/
	static std::set<Title*, ComparePtr<Title>> showMatchingTitles(gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR);

	/**
	* @brief Determines the average number of titles per user
	*
	* @return double Average number of titles per User
	*/
	double averageUserTitles() const;

	/**
	* @brief Determines the favorite platform of a User
	*
	* @param user Pointer to the User
	* @return string Favorite platform of User user
	*/
	std::string favoriteUserPlatform(User* user) const;

	/**
	* @brief Determines the total cost associated with a User library
	*
	* @param user Pointer to the User
	* @return double Total cost of the User user's library
	*/
	double userLibraryCost(User* user) const;

	/**
	* @brief Determines the average cost of a user's library
	*
	* @return double Average cost of a user's library
	*/
	double averageUserLibraryCost() const;

	/**
	* @brief Determines time spent by a User playing Online Titles
	*
	* @param user Pointer to User
	* @return double time spent by a User playing Online Titles
	*/
	double onlineTitlesPlayTime(User * user) const;

	/**
	* @brief Builds a list of a User's consuming habits
	*
	* @param user Pointer to the User
	* @param os Output stream to write to
	*/
	void buildUserConsumingHabitsList(User* user, std::ostream & os, ConsumingHabitsFilter chFilter);

	/**
	* @brief Updates the revenue of a Title
	* Fails if title does not exist
	*
	* @param title Pointer to the title
	* @param amount Value to be added
	* @return bool Returns true if successfull, false otherwise
	*/
	static bool updateTitleRevenue(Title* title, double amount);
	
	/**
	* @brief Get the pointer for a Title
	*
	* @param titleID ID of Title to get
	* @return Title* Pointer to the Title with ID titleID
	*/
	static Title* getTitle(unsigned int titleID);

	/**
	* @brief Get the pointer for a Title
	*
	* @param name Name of Title to get
	* @param platform Platform of Title
	* @return Title* Pointer to the Title with name name
	*/
	static Title* getTitle(std::string name, gameLibraryPlatform platform);

	/**
	* @brief Check if a Title is Adequate for an Age Group
	*
	* @param usr User to verify age
	* @param ageR Age Range in question
	* @return bool Returns true if adequate, false otherwise
	*/
	static bool userBelongsToAgeRange(const User * usr, ageRange ageR);

	/**
	* @brief Verifies if a Title is an Online Title
	*
	* @param title Pointer to title to verify
	* @return bool Returns true if it is an Online Title, false otherwise
	*/
	static bool isOnlineTitle(Title * title);

	std::vector<std::string> split(std::string long_string, int num_unique = 0);

	/**
	* @brief Calculates the purchase change of a user for a title
	*
	* @param usr User in question
	* @param title Title in question
	* @return float Returns the purchase chance
	*/
	float getPurchaseChance(User * usr, Title * title);

	// TODO: Comentar
	static Date getLibraryDate() { return libraryDate; };

	void goToDate(Date & d);

	void advanceXdays(unsigned int numberDays);

	void advanceXmonths(unsigned int numberMonths);

	void advanceXyears(unsigned int numberYears);

	// Generic function to update the users in all the Hash Tables
	void updateHashTable();

	// Use when game is bought and now he is active
	// TODO: verify statics
	static void removeFromHashTable(Title * title, User * user);

	// Use when date is fast forward
	// Adds user dependent of the last bought game
	void addSleepyUsers(unsigned int months);

	void addUserToHashTables(User * user);

};

/** @} */

#endif
