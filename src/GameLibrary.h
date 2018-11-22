#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H

#include <set>
#include <map>
#include <fstream>
#include "GameLibraryInfo.h"
#include "Title\Title.h"
#include "User\User.h"
#include "Utilities\Update.h"
#include "Utilities\CompareObj.h"

/** @defgroup GameLibrary Game Library Class
* @{
*
* GameLibrary Class represents a Game Library system to manage Users and Titles
* There are two types of Title, Home and Online.
* Users may buy, play and update Titles, as well as having other Users as friends.
*
* @see User
* @see Title
*/

class GameLibrary {
private:
	static std::set<Title*, ComparePtr<Title>> titles; /**< @brief Static Set of the Game Library Titles */
	static std::map<Title*, double, ComparePtr<Title>> titlesRevenue; /**< @brief Static Map of Titles to their respective total revenue */

	std::map<User*, std::set<Title*, ComparePtr<Title>>, ComparePtr<User>> users; /**< @brief Map of Users to their respective list of Titles */

public:
	/**
	* @brief Game Library class Destructor
	* Frees the space allocated for the Users and Titles
	*/
	~GameLibrary();

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

	// TODO: MARIO GIL espero que nao te importes disto!!!
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
	void loadGameLibraryFromFile(std::fstream& file);

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
	
};

/** @} */

#endif
