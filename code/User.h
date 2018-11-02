#ifndef USER_H
#define USER_H

class User {

private:
	String name;
	String email;
	int age;
	String address;
	vector<CreditCard> creditCards;
	map<Title*, TitleInfo> gamesList;
	set<User*> friendsList;
	std::vector<User> User;
	std::vector<User> Friend;

public:
	String getName();

	String getEmail();

	int getAge();

	String getAddress();

	bool addCreditCard(int CreditCard);

	bool hasTitle(int id);

	bool buyTitle(Title* title);

	bool updateTitle(HomeTitle* title);

	void addFriend(User* user);

	void removeFriend();

	User();

	void ~User();

	bool hasEnoughFunds(float price);

	void playGame(HomeTitle* title, int float_duration);

	void playGame(OnlineTitle* title, int float_duration);

	void paySubscription(OnlineTitle* title, int float_duration);
};

#endif
