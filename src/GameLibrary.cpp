#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "GameLibrary.h"
#include "Utilities\Exceptions.h"
#include "Title/HomeTitle.h"
#include "Title/OnlineTitle.h"
#include "Title/FixedSubscription.h"
#include "Title/DynamicSubscription.h"

using namespace std;

set<Title*, ComparePtr<Title>> GameLibrary::titles;
map<Title*, double, ComparePtr<Title>> GameLibrary::titlesRevenue;


GameLibrary::~GameLibrary()
{
	// Free space of users
	for (pair<User* const, set<Title*, ComparePtr<Title>>> & usr : users)
		delete usr.first;
	// Free space of titles
	for (Title * title : titles) 
		delete title;
}

void GameLibrary::addUser(std::string name, std::string email, int age, Address address)
{
	for (auto & user : users)
		if (email == user.first->getEmail())
			throw DuplicatedUser(email);

	User * newUser = new User(name, email, age, address);

	users.insert(pair<User*, set<Title*, ComparePtr<Title>>>(newUser, set<Title*, ComparePtr<Title>>()));

	// Assign user set of Titles to the User instance
	map<User*, set<Title*, ComparePtr<Title>>, ComparePtr<User>>::iterator it;
	for (it = users.begin(); it != users.end(); it++)
		if (it->first->getUserID() == newUser->getUserID())
		{
			it->first->setPurchasedGames(&(it->second));
			break;
		}
}

void GameLibrary::addUser(User * user) {
	users.insert(pair<User*, set<Title*, ComparePtr<Title>>>(user, set<Title*, ComparePtr<Title>>()));

	// Assign user set of Titles to the User instance
	map<User*, set<Title*, ComparePtr<Title>>, ComparePtr<User>>::iterator it;
	for (it = users.begin(); it != users.end(); it++)
		if (it->first->getUserID() == user->getUserID())
		{
			it->first->setPurchasedGames(&(it->second));
			break;
		}
}

bool GameLibrary::removeUser(User * user) {
	if (user == nullptr) return false;
	map<User*, set<Title*, ComparePtr<Title>>>::iterator it;
	it = users.find(user);
	if (it == users.end()) return false;
	users.erase(it);
	return true;
}

User * GameLibrary::getUser(string email)
{
	for (auto & user : users)
		if (user.first->getEmail() == email)
			return user.first;
	return nullptr;
}

bool GameLibrary::addTitle(Title * title) {
	bool repeated = false;
	for (const auto t : titles)
		if (t->getName() == title->getName() && t->getPlatform() == title->getPlatform())
		{
			repeated = true;
			break;
		}
	if (repeated) return false;
	titles.insert(title);
	return true;
}

bool GameLibrary::removeTitle(Title * title) {
	std::set<Title*, ComparePtr<Title>>::iterator it;
	it = titles.find(title);
	if (it == titles.end()) return false;
	titles.erase(it);
	return true;
}

bool GameLibrary::removeTitle(unsigned int id) {
	std::set<Title*, ComparePtr<Title>>::iterator it;
	for (it = titles.begin(); it != titles.end(); it++)
		if ((*it)->getTitleID() == id)
			break;
	if (it == titles.end()) return false;
	titles.erase(it);
	return true;
}

void GameLibrary::saveGameLibrary()
{
    // the info files only contains information on the number of games users
    ofstream library_info_file("info.txt");

    library_info_file << titles.size() << " " << users.size() << endl;
    library_info_file.close();

    system("mkdir titles >nul 2>nul");
    system("mkdir users >nul 2>nul");

	ostringstream user_file_name;
	ostringstream title_file_name;

	for (auto &user : users) {
	    // open one file per user and generate file name according to user_<id>.txt
	    user_file_name << "user_" << user.first->getUserID() << ".txt";
	    ofstream user_file("users/" + user_file_name.str());
	    user_file_name.str(""); // reset file name
	    user_file_name.clear();

	    // write user information including games by id
		user_file << user.first;
		user_file << "Games:" << endl;

		for (auto title : user.second) {
		    user_file << title->getTitleID() << endl;
		}

		user_file.close();
	}

	for (auto &set_it : titles) {
	    title_file_name << "title_" << set_it->getTitleID() << ".txt";
	    ofstream title_file("titles/" + title_file_name.str());
	    title_file_name.str("");
	    title_file_name.clear();

		set_it->displayTitleInfo(title_file);
		cout << endl;

		title_file << "Sales:" << endl;

	    for (const Sale &s : set_it->getSaleHistory()) {
	        title_file << s << endl;
	    }

	    title_file.close();
	}
}

void GameLibrary::loadGameLibraryFromFile(std::fstream& titleFile)
{/*
	ifstream info_file("info.txt");
	size_t ntitles, nusers;
	string str;

	enum title_states {
		id_name,
		price,
		platform_genre,
		age_range,
		title_types,
		release_date,
		subs_value,
		accept,
		session,
		sale_history,
	};

	enum user_states {
	    _id_name,
	    email_age,
	    address,
	    credit_cards,
	    transactions,
	    friends,
	};

	enum title_states title_current_state = id_name;
	enum user_states user_current_state = _id_name;

	if (!info_file) {
		cout << "Opening of information file failed. Does it exist?" << endl;
	}

	info_file >> ntitles >> nusers;

	ostringstream user_file_name;
	ostringstream title_file_name;

	for (size_t i = 1; i <= nusers; ++i) {
        string name, email, road_name, city, country, number, holder, expiry, transaction_date;
        int age, house_number, ncredit_cards, ntransactions, transaction_type;
        double balance, transaction_value;

	    user_file_name << "user_" << i << ".txt";
	    ifstream user_file("users/" + user_file_name.str());
	    user_file_name.str("");
	    user_file_name.clear();

	    Address addr;
	    vector<CreditCard> cc;
	    vector<Transaction> trans;

	    while(getline(user_file, str)) {

	        switch (user_current_state) {
	        case _id_name:
	            name = split(str)[1];
	            user_current_state = email_age;
	            break;
	        case email_age:
	            email = split(str)[0];
	            age = stoi(split(str)[1]);
	            getline(user_file, str);
	            if (str == "Address:") user_current_state = address;
	            break;
	        case address:
	            house_number = stoi(split(str)[0]);
	            road_name = split(str)[1];

	            getline(user_file, str);
	            city = str;
	            getline(user_file, str);
	            country = str;
	            getline(user_file, str);
	            if (str == "Credit Cards:") user_current_state = credit_cards;
	            getline(user_file, str);
	            ncredit_cards = stoi(str);
	            break;
	        case credit_cards:
	            number = split(str, 1)[0];
	            holder = split(str, 1)[1];

	            getline(user_file, str);
	            expiry = split(str)[0];
	            balance = stod(split(str)[1]);

	            cc.emplace_back(name, holder, expiry, balance);
	            --ncredit_cards;
	            if (ncredit_cards == 0) {
	                user_current_state = transactions;
	            }
	            break;
	        case transactions:
	            if (str == "Transactions:") { getline(user_file, str); ntransactions = stoi(str);}

	            getline(user_file, str);
	            transaction_type = stoi(split(str)[0]);
                transaction_date = split(str)[1];
                transaction_value = stod(split(str)[2]);

                trans.emplace_back(transaction_value, transaction_date, (TransactionType) transaction_type);
                --ntransactions;
                if (ntransactions == 0) { user_current_state = friends;}
                break;
	        case friends:
	            break;
	        default: break;
	        }
	    }
	    User *user = new User(name, email, age, Address(house_number, road_name, city, country));
	    addUser(user);

	    for (CreditCard &ccs : cc) {
	        user->addCreditCard(ccs);
	    }

	    for (Transaction & transaction : trans) {
	        user->addTransaction(transaction.getValue(), transaction.getDate(), transaction.getType());
	    }
	}

	for (size_t i = 1; i <= ntitles; ++i) {
		string title_name, _price, platform, genre, min_age, max_age, _release_date, _subs_value, company, title_type, subs_type, n_title_stats;

		title_file_name << "title_" << i << ".txt";
		ifstream title_file("titles/" + title_file_name.str());
		title_file_name.str("");
		title_file_name.clear();

		vector<string> sessions;
		vector<Sale> sales_history;

		while(getline(title_file, str)) {
			vector<string> split_line = split(str, 1);

			switch(title_current_state) {
			case id_name: title_name = split_line[1];
				title_current_state = price;
				break;
			case price:
			    _price = split_line[0];
			    company = split_line[1];
			    title_current_state = platform_genre;
			    break;
			case platform_genre: platform = split_line[0];
				genre = split_line[1];
				title_current_state = age_range;
				break;
			case age_range: min_age = split_line[0];
				max_age = split_line[1];
				title_current_state = release_date;
				break;
			case release_date:
			    _release_date = str;
				title_current_state = title_types;
				break;
			case title_types:
			    title_type = str;
			    title_current_state = accept;
			    break;
			case accept:
			    if (str == "Subscription Info:"){
    			    title_current_state = subs_value;
			    }
			    else if (str == "Sessions:") {
			        getline(title_file, str);
			        n_title_stats = str;
			        title_current_state = session;
			    } else if (str == "Sales:") {
			        title_current_state = sale_history;
			    }
				break;
			case subs_value:
			    _subs_value = split_line[0];
			    title_type = split_line[1];
			    title_current_state = accept;
			    break;
			case session: {
			    sessions.push_back(str);
			    int title_stats = stoi(n_title_stats);

			    --title_stats;
			    if (title_stats == 0) title_current_state = accept;
			    break;
			}
			case sale_history: {
			    vector<string> _split_line = split(str);
			    sales_history.emplace_back(_split_line[0], _split_line[1], _split_line[2]);
			}

			default:break;
			}
		}
		//Title(std::string name, double price, Date releaseDate, ageRange ageR, gameLibraryPlatform platform, gameLibraryGenre genre, std::string company);
        struct ageRange ar{stoi(min_age), stoi(max_age)};
        auto glp = (gameLibraryPlatform) stoi(platform);
        auto glg = (gameLibraryGenre) stoi(genre);

		if (title_type == "1") {
		    Title* title = new HomeTitle(title_name, stod(_price), Date(_release_date), ar, glp, glg, company);
		    addTitle(title);
		    for (Sale &sale : sales_history)
		        title->addPromotion(sale);
		}
		else if (title_type == "0") {
            if (subs_type == "0") {
                Title* online_title = new OnlineTitle(title_name, stod(_price), Date(_release_date), ar, glp, glg, company, new DynamicSubscription(stod(_subs_value)));
                addTitle(online_title);

                for (const string &s : sessions) {
                    vector<string> split_session = split(s);

                    auto user_id = static_cast<unsigned int>(stoi(split_session[0]));
                    Date session_date(split_session[1]);
                    double hours_played = stod(split_session[2]);

                    User *user = find_if(users.begin(), users.end(),
                        [user_id](const User* &user) {
                        return user->getUserID() == user_id;
                    })->first;

                    Session session = Session(hours_played, session_date);

                    online_title->addNewSession(user, session);
                }
            } else if (subs_type == "1") {
                addTitle(new OnlineTitle(title_name, stod(_price), Date(_release_date), ar, glp, glg, company, new FixedSubscription(stod(_subs_value))));
            }
		}
	}*/
}

bool GameLibrary::updateTitle(Title* title, Update * update) {
	try
	{
		title->updateTitle(update);
	}
	catch (NotHomeTitle)
	{
		cout << "(" << __func__ << ") Game Library tried to update Online Title " << title->getName() << endl;
		return false;
	}
	catch (OldUpdate & excp)
	{
		cout << "(" << __func__ << ") Tried to update title " << title->getName() << " from Current version " << excp.getCurrentVersion().getVersion();
		cout << " to Older version " << excp.getOldUpdate().getVersion() << endl;
		return false;
	}
	return true;
}

void GameLibrary::buildGlobalPopularityRanking(ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR) {
	
	map<int, const Title*> rankedList;
	
	// Search for all the titles that match and organize them by popularity
	for (const Title * title : titles)
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		int numberOfPlayers = title->getNumberUsers(ageR);
		rankedList.insert(pair<int, const Title*>(numberOfPlayers, title));
	}

	os << "Titles Popularity Ranking" << endl << endl;
	os << "Filters used:\n" << "Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << ", Age Group = " << ageR.minAge << " to " << ageR.maxAge << endl << endl;

	os << "N" << " " << "ID" << " " << "Name" << " " << "Popularity" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		// TODO FORMAT THE OUTPUT
		os << counter << ". " << entry.second->getTitleID() << " " << entry.second->getName() << " " << entry.first << endl;
		counter++;
	}	
}

void GameLibrary::buildGlobalRevenueRanking(ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR)
{
	map<double, const Title*> rankedList;

	// Search for all the titles that match and organize them by revenue
	for (Title * title : titles)
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		map<Title*, double, ComparePtr<Title>>::iterator it = titlesRevenue.find(title);
		rankedList.insert(pair<double, const Title*>((*it).second, title));
	}

	os << "Titles Revenue Ranking" << endl << endl;
	os << "Filters used:\n" << "Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << ", Age Group = " << ageR.minAge << " to " << ageR.maxAge << endl << endl;

	os << "N" << " " << "ID" << " " << "Name" << " " << "Revenue" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		// TODO FORMAT THE OUTPUT
		os << counter << ". " << entry.second->getTitleID() << " " << entry.second->getName() << " " << entry.first << endl;
		counter++;
	}
}

void GameLibrary::buildUserMostPlayedTitlesRanking(std::ostream & os, User * usr, gameLibraryPlatform platform, gameLibraryGenre genre)
{
	map<double, const Title*> rankedList;

	// Search for all the user titles that match and organize them by time played
	for (Title * title : *(usr->getPurchasedGames()))
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		try
		{
			double timePlayed = title->getTimePlayed(usr);
			rankedList.insert(pair<double, const Title*>(timePlayed, title));
		}
		catch (NotOnlineTitle) { continue; }
		catch (InexistentUser) { continue; }
	}

	os << "User Most Played Titles" << endl << endl;
	os << "Filters used:\n" << "Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << endl << endl;

	os << "N" << " " << "ID" << " " << "Name" << " " << "Hours Played" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		// TODO FORMAT THE OUTPUT
		os << counter << ". " << entry.second->getTitleID() << " " << entry.second->getName() << " " << entry.first << endl;
		counter++;
	}
}

double GameLibrary::averageUserTitles() const{
	double total = 0;
	for (const auto & user : users) total += user.second.size();
	return total / users.size();
}

string GameLibrary::favoriteUserPlatform(User* user) const {
	return user->getFavoritePlatform();
}

double GameLibrary::userLibraryCost(User* user) const {
	return user->getTotalTransactionsValue();
}

double GameLibrary::averageUserLibraryCost() const {
	double total = 0;
	for (const auto & user : users) total += userLibraryCost((User *)&user.first);
	return total / users.size();
}

double GameLibrary::onlineTitlesPlayTime(User * user) const
{
	double total = 0;
	for (const Title * title : *(user->getPurchasedGames()))
	{
		try
		{
			double time = title->getTimePlayed(user);
			total += time;
		}
		catch (NotOnlineTitle)
		{
			cout << "(" << __func__ << ") Game Library tried to get time played from Home Title " << title->getName() << endl;
			continue;
		}
		catch (InexistentUser)
		{
			cout << "(" << __func__ << ") Tried to get time played from title " << title->getName() << " for User ";
			cout << user->getName() << " who does not own the title" << endl;
			continue;
		}
	}
	return total;
}

void GameLibrary::buildUserConsumingHabitsList(User* user, ostream & os, ConsumingHabitsFilter chFilter)
{
	bool purchases = false, updates = false, subscriptions = false;
	switch (chFilter)
	{
	case pus: purchases = true;	updates = true;	subscriptions = true; break;
	case p:	purchases = true; break;
	case u:	updates = true;	break;
	case s:	subscriptions = true; break;
	case pu: purchases = true; updates = true; break;
	case ps: purchases = true; subscriptions = true; break;
	case us: updates = true; subscriptions = true; break;
	default: break;
	}

	os << "Consuming Habits of User " << user->getName() << ", ID = " << user->getUserID() << " :" << endl << endl;

	double purchasesTotal = 0, updatesTotal = 0, subsTotal = 0;
	int updatesCount = 0, subsCount = 0;
	for (const auto & trans : user->getTransactions())
	{
		if (trans.getType() == gamePurchase)
		{
			purchasesTotal += trans.getValue();
			if (purchases)
				os << trans << endl;
		}
		else if (trans.getType() == homeUpdate)
		{
			updatesCount++; 
			updatesTotal += trans.getValue();
			if (updates)
				os << trans << endl;
		}
		else if (trans.getType() == onlineSubscription)
		{
			subsCount++;
			subsTotal += trans.getValue();
			if (subscriptions)
				os << trans << endl;
		}
	}

	os << endl;
	if (purchases)
	{
		os << "Number of Titles Owned: " << (*(user->getPurchasedGames())).size() << endl;
		os << "Total spent purchasing Titles: " << purchasesTotal << endl;
	}
	if (updates)
	{
		os << "Number of Home Title Updates: " << updatesCount << endl;
		os << "Total spent updating Home Titles: " << updatesTotal << endl;
	}
	if (subscriptions)
	{
		os << "Number of Subscription Fees Payed: " << subsCount << endl;
		os << "Total spent paying Subscription Fees: " << subsTotal << endl;
	}
	if (purchases && updates && subscriptions)
	{
		os << "User Library Cost: " << (purchasesTotal + updatesTotal + subsTotal) << endl;
		os << "Account created on " << user->getCreationDate() << endl;
		os << "Favorite User Platform: " << favoriteUserPlatform(user) << endl;
		os << "Online Titles Playtime: " << onlineTitlesPlayTime(user) << endl;
		os << "Number of Friends: " << (user->getFriendsList()).size() << endl;
	}
}

bool GameLibrary::updateTitleRevenue(Title* title, double amount) {
	map<Title*, double, ComparePtr<Title>>::iterator it;
	it = titlesRevenue.find(title);
	if (it == titlesRevenue.end()) return false;
	(*it).second += amount;
	return true;
}

Title * GameLibrary::getTitle(unsigned int titleID)
{
	for (auto & title : titles)
		if (title->getTitleID() == titleID)
			return const_cast<Title*>(title);
	return nullptr;
}

Title * GameLibrary::getTitle(std::string name, gameLibraryPlatform platform)
{
	for (auto & title : titles)
		if (title->getName() == name && title->getPlatform() == platform)
			return const_cast<Title*>(title);
	return nullptr;
}

bool GameLibrary::userBelongsToAgeRange(const User * usr, ageRange ageR)
{
	return (usr->getAge() >= ageR.minAge && usr->getAge() <= ageR.maxAge);
}

bool GameLibrary::isOnlineTitle(Title * title)
{
	try
	{
		title->getSubscription();
	}
	catch (NotOnlineTitle)
	{
		return false;
	}
	return true;
}

vector<string> GameLibrary::split(std::string long_string, int num_unique)
{
	vector<string> result;
	size_t i = 0;
	size_t space_index = long_string.find_first_of(' '), j = space_index;

	if (space_index != string::npos && num_unique == 1) {
        result.push_back(long_string.substr(0, space_index));
        result.push_back(long_string.substr(space_index + 1));
	} else if (space_index != string::npos) {
	    while(space_index != string::npos) {
	        string sub = long_string.substr(i, j);
	        result.push_back(sub);
	        space_index = sub.find_first_of(' ');
	        i = j + 1;
	        j = space_index;
	    }
	}

	return result;
}
