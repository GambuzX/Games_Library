#ifndef USER_H
#define USER_H

class User {

private:
	string name;
	string email;
	int age;
	Address address;
	vector<CreditCard> creditCards;
	set<Title*>* purchasedGames;
	unsigned int userID;
	vector<User*> friendsList;

public:
	void addCreditCard(CreditCard cc);

	bool hasTitle(Title title);

	bool hasTitle(unsigned int titleID);

	void buyTitle(Title* title);

	void buyTitle(unsigned int titleID);

	void updateTitle(Title* title);

	void updateTitle(unsigned int titleID);

	void playGame();

	void addFrienc();

	void removeFriend();
};

#endif
