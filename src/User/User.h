#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include "..\Utilities\buy_chance.h"
#include "..\Title\Title.h"
#include "..\Utilities\CreditCard.h"
#include "..\Utilities\Transaction.h"
#include "..\Utilities\Address.h"
#include "..\Utilities\WishlistEntry.h"
#include "..\Utilities\CompareObj.h"

class Title;
class WishlistEntry;


/** @defgroup User Users
* @ingroup GameLibrary
* @{
*
* @brief Group holding all the information about Users and related classes.
*
* This group contains the class User and others which are related to it.
*
*
* @see User
* @see CreditCard
* @see Address
* @see Transaction
*/

typedef std::map<Title*, std::tuple<unsigned int, unsigned int>, ComparePtr<Title>> mapTitleTuple;

/**
* @brief Class that represents an User in the Game Library
*/
class User {

private:
	static unsigned int nextUserID; /**< @brief Static Unsigned Int used to assign different IDs to each User */
	const unsigned int userID; /**< @brief Unsigned Int with the user ID */
	Date createdDate; /**< @brief Date the User account was created */
	std::string name; /**< @brief String with the user name */
	std::string email; /**< @brief String with the user email */
	int age; /**< @brief Int with the user age */
	Address address; /**< @brief Address of the user */
	std::vector<CreditCard> creditCards; /**< @brief Vector of the user CreditCards */
	std::set<Title*, ComparePtr<Title>>* purchasedGames; /**< @brief Pointer to this user's set of purchased games */
	std::set<User*, ComparePtr<User>> friendsList; /**< @brief Set with the user friends */
	std::vector<Transaction> transactions; /**< @brief Vector with the user transactions */
	std::priority_queue<WishlistEntry> wishlist; /**< @brief Priority queue representing the user wishlist  */
	mapTitleTuple searches_ads; /**< @brief Map of Titles to a tuple with the number of searches for that title and the ads of the same title seen */

public:
	/**
	* @brief Construct a new User object
	* Uses the nextUserID static int to assign the userID
	* Assigns the current library Date to createdDate
	*
	* @param name String that initializes the name Private Member
	* @param email String that initializes the email Private Member
	* @param age Int that initializes the age Private Member
	* @param address Address that initializes the address Private Member
	*/
	User (std::string name, std::string email, int age, Address address);

	/**
	 * @brief Get the Number Of Searches of the desired Title
	 * 
	 * @param title From which we want to know the number of times that has been searched
	 * @return unsigned int Number of times that has been searched a certain Title
	 */
	unsigned int getNumberOfSearches(Title * title) { return std::get<0>(searches_ads[title]); };

	/**
	 * @brief Get the Number Of Seen Ads of the desired Title
	 * 
	 * @param title From which we want to know the number of times that an add has been seen
	 * @return unsigned int Number of times that has been seen an add from a certain Title
	 */
	unsigned int getNumberOfSeenAds(Title * title) { return std::get<1>(searches_ads[title]); };

	/**
	 * @brief Increment the number of times that a certain title has been searched
	 * 
	 * @param title Title that has been searched
	 */
	void incNumberOfSearches(Title * title) { ++std::get<0>(searches_ads[title]); };

	/**
	 * @brief Increment the number of times that an add from a certain title has been seen
	 * 
	 * @param title Title from which the add was seen
	 */
	void incNumberOfSeenAds(Title * title) { ++std::get<1>(searches_ads[title]); };

	/**
	 * @brief Adds a New Title to the searches_ads map and initializes the searches and the number of seen ads to 0
	 * 
	 * @param title Title to be added to the map
	 * @return true If the insertion was completed
	 * @return false If there was already a title in the map
	 */
	bool addTitleToTupleMap(Title * title) { return (searches_ads.insert(std::pair<Title*, std::tuple<unsigned int, unsigned int>>(title, std::make_tuple(0, 0)))).second; }

	/**
	 * @brief Removes a Title from the search_ads map
	 * 
	 * @param title Pointer to the Title to be removed
	 * @return true If the title was removed
	 * @return false If there was no title to be removed
	 */
	bool removeTitleFromTupleMap(Title * title) { return searches_ads.erase(title); };
	
	/**
	* @brief Get the createdDate Private Member
	*
	* @return Date Returns the createdDate Private Member
	*/
	Date getCreationDate() const { return createdDate; }

	/**
	* @brief Get the name Private Member
	*
	* @return string Returns the name Private Member
	*/
	std::string getName() const { return name; }

	/**
	* @brief Get the userID Private Member
	*
	* @return int Returns the userID Private Member
	*/
	unsigned int getUserID() const { return userID; }

	/**
	* @brief Get the email Private Member
	*
	* @return string Returns the email Private Member
	*/
	std::string getEmail() const { return email; }

	/**
	* @brief Get the age Private Member
	*
	* @return int Returns the age Private Member
	*/
	int getAge() const { return age; }

	/**
	* @brief Get the address Private Member
	*
	* @return Address Returns the address Private Member
	*/
	Address getAddress() const { return address; }

	/**
	* @brief Get the creditCards Private Member
	*
	* @return const vector<CreditCard> & Returns the creditCards Private Member
	*/
	const std::vector<CreditCard> & getCreditCards() const { return creditCards; }

	/**
	* @brief Get the Credit Cards with the specified number
	*
	* @param creditCardNumber String with the Credit Card Number that we want
	* @return const CreditCard * Returns the Credit Card with the Desired Number or NULL if it does not exists
	*/
	CreditCard * getCreditCard(std::string creditCardNumber);

	/**
	* @brief Get the purchasedGames Private Member
	*
	* @return const set<Title*>* Returns the purchasedGames Private Member
	*/
	const std::set<Title*, ComparePtr<Title>>* getPurchasedGames() const { return purchasedGames; }

	/**
	* @brief Get the friendsList Private Member
	*
	* @return const set<User*, ComparePtr<User>> & Returns the friendsList Private Member
	*/
	const std::set<User*, ComparePtr<User>> & getFriendsList() const { return friendsList; }

	/**
	* @brief Get the transactions Private Member
	*
	* @return const vector<Transaction> & Returns the transactions Private Member
	*/
	const std::vector<Transaction> & getTransactions() const { return transactions; }

	/**
	* @brief Get the Wishlist Private Member
	*
	* @return const priority_queue<WishlistEntry> & Returns the wishlist Private Member
	*/
	const std::priority_queue<WishlistEntry> & getWishlist() const { return wishlist; }

	/**
	* @brief Set the createdDate Private Member
	*
	* @param date Date to set the createdDate to
	*/
	void setCreatedDate(const Date & date) { createdDate = date; }
	
	// TODO: Comentar
	void setAge(const int newAge) { age = newAge; }

	/**
	* @brief Set the purchasedGames Private Member
	*
	* @param games Pointer to the User's game list
	*/
	void setPurchasedGames(std::set<Title*, ComparePtr<Title>> * games) { purchasedGames = games; }

	/**
	* @brief Get the total value of the user's transactions
	*
	* @return double Returns the total value of user's transactions
	*/
	double getTotalTransactionsValue() const;

	/**
	* @brief Get the user's favorite platform
	* The favorite platform is defined as the platform for which the user has more titles
	*
	* @return string Returns the user's favorite platform
	*/
	std::string getFavoritePlatform() const;

	/**
	* @brief Adds a CreditCard to the user's creditCards Private Member
	*
	* @param cc Credit Card to add
	* @return bool Returns true if successfull, false otherwise
	*/
	bool addCreditCard(CreditCard cc);

	/**
	* @brief Removes a CreditCard to the user's creditCards Private Member
	*
	* @param creditCardNumber Credit Card Number to be removed
	* @return bool Returns true if successfull, false otherwise
	*/
	bool removeCreditCard(std::string creditCardNumber);

	/**
	* @brief Verifies if the user's balance is enough for parameter val
	*
	* @param val Value to be compared
	* @return bool Returns true if user has enough money, false otherwise
	*/
	bool hasEnoughMoney(double val) const;

	/**
	* @brief Subtracts the value val to the user's balance
	* Tries to reduce CreditCard balance in a try catch
	*
	* @param val Value to be subtracted
	* @return bool Returns true if successfull, false otherwise
	*/
	bool subtractValue(double val);

	/**
	* @brief Verify if User has Title
	*
	* @param title Title to search
	* @return bool Returns true if user has it, false otherwise
	*/
	bool hasTitle(Title* title) const;

	/**
	* @brief Verify if User has Title
	* Uses GameLibrary's static method getTitle() to retrieve information about the Title with ID titleID
	*
	* @param titleID ID of Title to search
	* @return bool Returns true if user has it, false otherwise
	*/
	bool hasTitle(unsigned int titleID) const;

	/**
	* @brief Verify if User has Title
	* Uses GameLibrary's static method getTitle() to retrieve information about the Title with name name
	*
	* @param name Name of Title to search
	* @param platform Platform of title
	* @return bool Returns true if user has it, false otherwise
	*/
	bool hasTitle(std::string name, gameLibraryPlatform platform) const;

	/**
	* @brief Buy Title for User
	* Verifies if User already owns title
	* Updates GameLibrary's titleRevenue map
	* Adds a transaction to User
	*
	* @param title Pointer to Title to buy
	* @return bool Returns true if successfull, false otherwise
	*/
	bool buyTitle(Title* title);

	/**
	* @brief Buy Title for User
	* Uses GameLibrary's static method getTitle() to retrieve information about the Title with id titleID
	*
	* @param titleID ID of Title to buy
	* @return bool Returns true if successfull, false otherwise
	*/
	bool buyTitle(unsigned int titleID);

	/**
	* @brief Buy Title for User
	* Uses GameLibrary's static method getTitle() to retrieve information about the Title with name name
	*
	* @param name Name of Title to buy
	* @param platform Platform of Title
	* @return bool Returns true if successfull, false otherwise
	*/
	bool buyTitle(std::string name, gameLibraryPlatform platform);

	/**
	* @brief Add a Title to the User list
	* Does not perform a purchase
	*
	* @param titleID ID of Title to add
	* @return bool Returns true if successfull, false otherwise
	*/
	bool addTitle(unsigned int titleID);

	/**
	* @brief Update User version of a Title
	*
	* @param title Pointer to Title to update
	* @return bool Returns true if successfull, false otherwise
	*/
	bool updateTitle(Title* title);

	/**
	* @brief Update User version of a Title
	* Uses GameLibrary's static method getTitle() to retrieve information about the Title with id titleID
	*
	* @param titleID ID of Title to update
	* @return bool Returns true if successfull, false otherwise
	*/
	bool updateTitle(unsigned int titleID);

	/**
	* @brief Play a Title
	*
	* @param title Pointer to the Title the User played
	* @param duration Time in hours of the playing sessions
	* @return bool Returns true if successfull, false otherwise
	*/
	bool playGame(Title * title, double duration);

	/**
	* @brief Adds a User to the friendsList Private Member
	*
	* @param frnd Pointer to the User to add as friend
	* @return bool Returns true if successfull, false otherwise
	*/
	bool addFriend(User * frnd);

	/**
	* @brief Removes a User from the friendsList Private Member
	*
	* @param frnd Pointer to the User to remove as friend
	* @return bool Returns true if successfull, false otherwise
	*/
	bool removeFriend(User * frnd);

	/**
	* @brief Adds a Transaction to the User
	*
	* @param value Value of transaction
	* @param date Date of transaction
	* @param t TransactionType enum value representing the type of transaction
	* @param titleID ID of the title of the transaction
	*/
	void addTransaction(double value, Date date, TransactionType t, unsigned int titleID) { transactions.push_back(Transaction(value, date, t, titleID)); }

	/**
	* @brief Returns the Title in the wishlist of higher priority, with a minimum buy rate
	*
	* @param minimumBuyRate Minimum buy rate for the title to find
	* @return WishlistEntry * Copy of WishlistEntry of most priority
	*/
	WishlistEntry nextAdvertisementTitle(float minimumBuyRate);
	
	//TODO: ver Next Advertsiment mas minimunBuyRate e o especificado pelo fabricante do title
	WishlistEntry nextAdvertisementTitle();

	/**
	* @brief Creates an entry for the wishlist
	*
	* @param interest Interest in the title, from 1 to 10
	* @param buyChance Chance of the user buying this title, between 0 and 1
	* @param title Pointer to the title
	* @return bool Returns true if successfull, false otherwise
	*/
	bool addWishlistEntry(unsigned interest, float buyChance, Title * title);

	/**
	* @brief Creates an entry for the wishlist
	*
	* @param interest Interest in the title, from 1 to 10
	* @param title Pointer to the title
	* @return bool Returns true if successfull, false otherwise
	*/
	bool addWishlistEntry(unsigned interest, Title * title);

	/**
	* @brief Removes an entry from the wishlist
	*
	* @param title Pointer to the title to remove
	* @return bool Returns true if successfull, false otherwise
	*/
	bool removeWishlistEntry(Title * title);

	/**
	* @brief Edits an entry in the wishlist
	*
	* @param title Pointer to the title to edit
	* @param interest Interest in the title, from 1 to 10
	* @return bool Returns true if successfull, false otherwise
	*/
	bool editWishlistEntry(Title * title, unsigned interest);
	//TODO: comentar
	void updateWishlistProbability();

	const WishlistEntry & getWishlistEntry(Title * title);

	/**
	* @brief Get a set with all the Platforms the User has titles for
	*
	* @return set<string> with a string for each platform the User has Titles for
	*/
	std::set<std::string> getPlatforms();

	/**
	* @brief Overload of the less operator
	* A User is "less" than the other if its ID is smaller
	*
	* @param usr User to compare the "current" User to
	* @return bool Returns the result of the IDs comparison
	*/
	bool operator<(const User & usr) const;

	friend std::ostream& operator<<(std::ostream &os, const User &user);

};

enum UserCmpType
{
	ID,
	ADS,
	SEARCHES,
	BUYCHANCE
};

class CompareUsr
{
private:
	Title * title;
	UserCmpType cmp_type;
public:
	CompareUsr(UserCmpType cmp) { title = nullptr; cmp_type = cmp; }
	CompareUsr(Title* title, UserCmpType cmp) { this->title = title; cmp_type = cmp; }
	bool operator()(User * usr1, User * usr2)
	{
		if (title == nullptr) return *usr1 < *usr2;
		switch (cmp_type)
		{
		case ID:
			return *usr1 < *usr2;
		case ADS:
			return usr1->getNumberOfSeenAds(title) > usr2->getNumberOfSeenAds(title);
		case SEARCHES:
			return usr1->getNumberOfSearches(title) > usr2->getNumberOfSearches(title);
		case BUYCHANCE:
			return sigmoid(f(usr1, title)) > sigmoid(f(usr2, title));
			//return usr1->getWishlistEntry(title).getBuyChance() > usr2->getWishlistEntry(title).getBuyChance();
		}

		return *usr1 < *usr2;
	}
};

/** @} */

#endif
