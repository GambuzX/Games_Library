#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <set>
#include "CreditCard.h"
#include "Title.h"
#include "Transaction.h"
#include "Address.h"

class User {

private:
	static int nextUserID;
	unsigned int userID;
	std::string name;
	std::string email;
	int age;
	Address address;
	std::vector<CreditCard> creditCards;
	std::set<Title*>* purchasedGames;
	std::set<User*> friendsList;
	std::vector<Transaction> transactions;

public:
	User (std::string name, std::string email, int age, Address address);

	std::string getName() const { return name; }
	std::string getEmail() const { return email; }
	int getAge() const { return age; }
	Address getAddress() const { return address; }
	const std::vector<CreditCard> & getCreditCards() const { return creditCards; }
	const std::set<Title*>* getPurchasedGames() const { return purchasedGames; }
	const std::set<User*> & getFriendsList() const { return friendsList; }
	const std::vector<Transaction> & getTransactions() const { return transactions; }

	void addCreditCard(CreditCard cc);

	bool hasTitle(Title* title);

	bool hasTitle(unsigned int titleID);

	void buyTitle(Title* title);

	void buyTitle(unsigned int titleID);

	void updateTitle(Title* title);

	void updateTitle(unsigned int titleID);

	void playGame();

	void addFriend();

	void removeFriend();
};

#endif
