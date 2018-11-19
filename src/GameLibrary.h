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

	std::map<User, std::set<Title*, ComparePtr<Title>>> users; /**< @brief Map of Users to their respective list of Titles */
	/*std::vector<std::string> supportedPlatforms;
	std::vector<std::string> titlesGenres;
	std::vector<std::string> ageGroups;*/

public:
	/**
	* @brief Construct a new Game Library object
	*
	* @param platforms Vector of strings representing the supported platforms
	* @param genres Vector of strings representing the supported title genres
	* @param ages Vector of strings representing the defined ageGroups
	*/
	//GameLibrary(std::vector<std::string> * platforms, std::vector<std::string> * genres, std::vector<std::string> * ages) : supportedPlatforms(*platforms), titlesGenres(*genres), ageGroups(*ages) {}

	/**
	* @brief Adds a User to the Game Library
	* Constructs a new user with the given parameters
	*
	* @param name String that initializes the User's name
	* @param email String that initializes the User's email
	* @param age Int that initializes the User's age
	* @param address Address that initializes the User's address
	*/
	void addUser(std::string name, std::string email, int age, Address address);

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
	* @brief Adds a Title to the Game Library
	*
	* @param user Pointer to the Title to be added
	*/
	void addTitle(Title * title);

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
	* @brief Saves the current Game Library and all of its data to a file
	*
	* @param file File to save the data to
	*/
	void saveGameLibraryToFile(std::fstream& file);

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
	* @brief Builds a popularity ranking of the Titles
	* Ranking is based on the combination of the 3 parameters provided
	*
	* @param platform Filter to limit ranking to this platform
	* @param genre Filter to limit ranking to this genre
	* @param ageR Filter to limit ranking to this age group
	*/
	void buildPopularityRanking(std::ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR);

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
	* @return Title* Pointer to the Title with name name
	*/
	static Title* getTitle(std::string name);

	/**
	* @brief Get the name of a platform
	*
	* @param platform Enum type of the platform
	* @return string Returns the name of the platform provided as argument
	*/
	static std::string getPlatformName(gameLibraryPlatform platform);

	/**
	* @brief Get the name of a genre
	*
	* @param genre Enum type of the genre
	* @return string Returns the name of the genre provided as argument
	*/
	static std::string getGenreName(gameLibraryGenre genre);

	/**
	* @brief Check if a Title is Adequate for an Age Group
	*
	* @param usr User to verify age
	* @param ageR Age Range in question
	* @return bool Returns true if adequate, false otherwise
	*/
	static bool userBelongsToAgeRange(const User * usr, ageRange ageR);
	
};

/** @} */

#endif
