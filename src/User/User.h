#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <set>
#include "..\Utilities\CreditCard.h"
#include "..\Title\Title.h"
#include "..\Utilities\Transaction.h"
#include "..\Utilities\Address.h"
#include "..\Utilities\CompareObj.h"

class User {

private:
	static int nextUserID;
	const unsigned int userID;
	std::string name;
	std::string email;
	int age;
	Address address;
	std::vector<CreditCard> creditCards;
	std::set<Title*>* purchasedGames;
	std::set<User*, CompareUserPtr> friendsList;
	std::vector<Transaction> transactions;

public:
	User (std::string name, std::string email, int age, Address address);

	std::string getName() const { return name; }
	unsigned int getUserID() const { return userID; }
	std::string getEmail() const { return email; }
	int getAge() const { return age; }
	Address getAddress() const { return address; }
	const std::vector<CreditCard> & getCreditCards() const { return creditCards; }
	const std::set<Title*>* getPurchasedGames() const { return purchasedGames; }
	const std::set<User*, CompareUserPtr> & getFriendsList() const { return friendsList; }
	const std::vector<Transaction> & getTransactions() const { return transactions; }

	bool addCreditCard(CreditCard cc);
	bool hasEnoughMoney(double val) const;
	bool subtractValue(double val);

	bool hasTitle(Title* title) const;
	bool hasTitle(unsigned int titleID) const;

	bool buyTitle(Title* title);
	bool buyTitle(unsigned int titleID);
	bool updateTitle(Title* title);
	bool updateTitle(unsigned int titleID);

	bool playGame();

	bool addFriend(User * frnd);
	bool removeFriend(User * frnd);

	bool operator<(const User & usr) const;
};

#endif
