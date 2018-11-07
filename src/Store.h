#ifndef STORE_H
#define STORE_H

class Store {

private:
	set<Title> titles;
	map<User, set<Title*>> users;

public:
	void addUser(User* user);

	void addTitle(Title* title);

	void removeTitle(unsigned int id);

	void loadTitlesFromFile(fstream& titleFile);

	void loadUsersFromFile(fstream& userFile);

	void buyTitle(User user, Title* title);

	void buyTitle(int userID, int titleID);
};

#endif
