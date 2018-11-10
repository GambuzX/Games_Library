#ifndef USER_H
#define USER_H

class User {

private:
	static int nextUserID;
	unsigned int userID;
	string name;
	string email;
	int age;
	Address address;
	vector<CreditCard> creditCards;
	set<Title*>* purchasedGames;
	set<User*> friendsList;
	vector<Transaction> transactions;

public:
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
