#include <iostream>
#include <iomanip>
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

class GameLibrary;

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
	for (auto & u : users)
		if (user->getEmail() == u.first->getEmail())
			throw DuplicatedUser(user->getEmail());

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

	pair<titlesSet::iterator, bool> it = titles.insert(title);
	if (it.second)
		titlesRevenue.insert(pair<Title*, double>(title, 0));
	return it.second;
}

bool GameLibrary::removeTitle(Title * title) {
	titleSet::iterator it;
	it = titles.find(title);
	if (it == titles.end()) return false;
	titles.erase(it);

	titlesRevenueMap::iterator it2;
	it2 = titlesRevenue.find(title);
	if (it2 == titlesRevenue.end()) return false;
	titlesRevenue.erase(it2);
	return true;
}

bool GameLibrary::removeTitle(unsigned int id) {
	Title * title = getTitle(id);
	if (title == nullptr) return false;

	titleSet::iterator it;
	it = titles.find(title);
	if (it == titles.end()) return false;
	titles.erase(it);

	titlesRevenueMap::iterator it2;
	it2 = titlesRevenue.find(title);
	if (it2 == titlesRevenue.end()) return false;
	titlesRevenue.erase(it2);
	return true;
}

bool GameLibrary::addCompany(Company * comp)
{
	pair<companiesSet::iterator, bool> it = platformCompanies.insert(comp);
	return it.second;
}

bool GameLibrary::removeCompany(Company * comp)
{
	companiesSet::iterator it = platformCompanies.find(comp);
	if (it == platformCompanies.end()) return false;
	platformCompanies.erase(it);
	return true;
}

Company * GameLibrary::getCompany(string name)
{
	companiesSet::iterator it;
	for (it = platformCompanies.begin(); it != platformCompanies.end(); it++)
		if ((*it)->getName() == name) return *it;
	return nullptr;
}

bool GameLibrary::editCompany(std::string name, unsigned NIF, unsigned contact)
{
	Company * comp = getCompany(name);
	if (comp == nullptr) return false;
	
	comp->setNIF(NIF);
	comp->setContact(contact);
	return true;
}

bool GameLibrary::addTitleToCompany(string companyName, Title * title)
{
	Company * comp = getCompany(companyName);
	if (comp == nullptr) return false;

	return comp->addTitle(title);
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
		user_file << *(user.first);
		user_file << "Games:" << endl;
		user_file << user.second.size() << endl;

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

void GameLibrary::loadGameLibrary()
{
	if (!titles.empty() || !users.empty()) { throw AlreadyLoaded(); }
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
		update,
		sale_history,
	};

	enum user_states {
		_id_name,
		email_age,
		address,
		credit_cards,
		transactions,
		friends,
		games,
	};

	enum title_states title_current_state = id_name;
	enum user_states user_current_state = _id_name;

	if (!info_file) {
		cout << "Opening of information file failed. Does it exist?" << endl;
	}

	info_file >> ntitles >> nusers;

	ostringstream user_file_name;
	ostringstream title_file_name;

	vector<pair<unsigned int, vector<unsigned int>>> allfriends, allgames;

	for (size_t i = 1; i <= nusers; ++i) {
		string name, email, road_name, city, country, number, holder, expiry, transaction_date;
		int age, house_number, ncredit_cards, ntransactions=0, transaction_type, nfriends, ngames;
		double balance, transaction_value;

		user_file_name << "user_" << i << ".txt";
		ifstream user_file("users/" + user_file_name.str());
		user_file_name.str("");
		user_file_name.clear();

		Address addr;
		vector<CreditCard> cc;
		vector<Transaction> trans;
		vector<unsigned int> friend_ids, game_ids;

		while(getline(user_file, str)) {

			switch (user_current_state) {
			case _id_name:
				name = split(str, 1)[1];
				user_current_state = email_age;
				break;
			case email_age:
				email = split(str)[0];
				age = stoi(split(str, 1)[1]);
				getline(user_file, str);
				if (str == "Address:") user_current_state = address;
				break;
			case address:
				house_number = stoi(split(str)[0]);
				road_name = split(str, 1)[1];

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
				if (ncredit_cards == 0) {
					user_current_state = transactions;
					getline(user_file, str);
					ntransactions = stoi(str);
					break;
				}
				number = split(str, 1)[0];
				holder = split(str, 1)[1];

				getline(user_file, str);
				expiry = split(str)[0];
				balance = stod(split(str, 1)[1]);

				cc.emplace_back(name, holder, expiry, balance);
				--ncredit_cards;
				break;
			case transactions:
				if (ntransactions == 0) { user_current_state = friends; getline(user_file, str); nfriends = stoi(str); break;}

				transaction_type = stoi(split(str, 1)[0]);
				transaction_date = split(str, 1)[1];

				getline(user_file, str);
				transaction_value = stod(str);

				trans.emplace_back(transaction_value, transaction_date, (TransactionType) transaction_type);
				--ntransactions;
				break;
			case friends:
				if (nfriends == 0) {
					user_current_state = games;
					getline(user_file, str);
					ngames = stoi(str);
					break;
				}

				friend_ids.push_back(static_cast<unsigned int &&>(stoi(str)));
				--nfriends;
				break;
			case games:
				if (ngames == 0) { break; }
				game_ids.push_back(static_cast<unsigned int &&>(stoi(str)));
				--ngames;
			default: break;
			}
		}
		user_current_state = _id_name;
		User *user = new User(name, email, age, Address(house_number, road_name, city, country));
		addUser(user);

		for (CreditCard &ccs : cc) {
			user->addCreditCard(ccs);
		}

		for (Transaction & transaction : trans) {
			user->addTransaction(transaction.getValue(), transaction.getDate(), transaction.getType());
		}

		allfriends.emplace_back(i, friend_ids);
		allgames.emplace_back(i, game_ids);
		user_file.close();
	}

	for (pair<unsigned int, vector<unsigned int>> &friends_list : allfriends) {
		User* user = find_if(users.begin(), users.end(),
							 [friends_list](const std::pair<User* const, std::set<Title*, ComparePtr<Title>>> &user) {
								 return user.first->getUserID() == friends_list.first;
							 })->first;

		if (user == nullptr) break;

		for (unsigned int &f : friends_list.second) {
			User* fr = find_if(users.begin(), users.end(),
							   [f](const std::pair<User* const, std::set<Title*, ComparePtr<Title>>> &user) {
								   return user.first->getUserID() == f;
							   })->first;

			if (fr == nullptr) break;
			user->addFriend(fr);
		}

	}

	for (size_t i = 1; i <= ntitles; ++i) {
		string title_name, _price, platform, genre, min_age, max_age, _release_date, _subs_value, company, title_type, subs_type, n_title_stats, update_date, description;
		int n_updates, title_stats;
		double update_price, update_version;

		title_file_name << "title_" << i << ".txt";
		ifstream title_file("titles/" + title_file_name.str());
		title_file_name.str("");
		title_file_name.clear();

		vector<string> sessions;
		vector<Sale> sales_history;
		vector<Update> update_vector;

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
					title_stats = stoi(str);
					title_current_state = session;
				} else if (str == "Sales:") {
					title_current_state = sale_history;
				} else if (str == "Updates:") {
					title_current_state = update;
					getline(title_file, str);
					n_updates = stoi(str);
				}
				break;
			case subs_value:
				_subs_value = split_line[0];
				subs_type = split_line[1];
				title_current_state = accept;
				break;
			case session: {
				if (title_stats == 0){
					if (str == "Sales:") { title_current_state = sale_history; break;}
					title_current_state = accept;
					break;
				}
				sessions.push_back(str);

				--title_stats;
				break;
			}
			case sale_history: {
				vector<string> _split_line = split(str);
				sales_history.push_back(Sale(Date(_split_line[0]), Date(_split_line[1]), stod(_split_line[2])));
				break;
			}
			case update: {
				if (n_updates == 0) {
					title_current_state = accept;
					break;
				}
				update_date = split_line[0];
				description = split_line[1];

				getline(title_file, str);
				split_line = split(str, 1);
				update_version = stod(split_line[0]);
				update_price = stod(split_line[1]);

				update_vector.emplace_back(update_date, description, update_version, update_price);
				--n_updates;
				break;
			}

			default:break;
			}
		}
		title_current_state = id_name;
		//Title(std::string name, double price, Date releaseDate, ageRange ageR, gameLibraryPlatform platform, gameLibraryGenre genre, std::string company);
		struct ageRange ar{stoi(min_age), stoi(max_age)};
		auto glp = (gameLibraryPlatform) stoi(platform);
		auto glg = (gameLibraryGenre) stoi(genre);

		if (title_type == "1") {
			Title* title = new HomeTitle(title_name, stod(_price), Date(_release_date), ar, glp, glg, company);
			addTitle(title);
			for (Sale &sale : sales_history)
				title->addPromotion(sale);
			title->resetUpdates();
			for (Update up_date : update_vector)
				this->updateTitle(title, &up_date);
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
										 [user_id](const std::pair<User* const, std::set<Title*, ComparePtr<Title>>> &user) {
											 return user.first->getUserID() == user_id;
										 })->first;

					Session session = Session(hours_played, session_date);

					try {
						online_title->addNewSession(user, session);
					} catch (InexistentUser) {
						user->addTitle(online_title->getTitleID());
						online_title->addNewSession(user, session);
					}

				}

				for (Sale sale : sales_history)
					online_title->addPromotion(sale);

				for (Update up_date : update_vector)
					this->updateTitle(online_title, &up_date);

			} else if (subs_type == "1") {
				Title* online_titl = new OnlineTitle(title_name, stod(_price), Date(_release_date), ar, glp, glg, company, new FixedSubscription(stod(_subs_value)));
				addTitle(online_titl);

				for (Sale sale : sales_history)
					online_titl->addPromotion(sale);

				for (Update up_date : update_vector)
					this->updateTitle(online_titl, &up_date);
			}
		}
		title_file.close();
	}

	for (pair<unsigned int, vector<unsigned int>> &games_list : allgames) {
		User* user = find_if(users.begin(), users.end(),
							 [games_list](const std::pair<User* const, std::set<Title*, ComparePtr<Title>>> &user) {
								 return user.first->getUserID() == games_list.first;
							 })->first;

		if (user == nullptr) break;

		for (unsigned int &id : games_list.second) {
			try{
				user->addTitle(id);
			} catch (DuplicatedUser) {
				continue;
			}
		}
	}
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

void GameLibrary::buildGlobalPopularityRanking(ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR)
{

	unsigned widthID = 3, widthName = 15, witdthR = 15, widthIn = 3;

	multimap<int, const Title*, DecrescentOrder<int>> rankedList;

	// Search for all the titles that match and organize them by popularity
	for (const Title * title : titles)
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		//if (!(title->getAgeRange().minAge >= ageR.minAge && title->getAgeRange().maxAge <= ageR.maxAge)) continue;
		int numberOfPlayers = title->getNumberUsers(ageR);
		if (title->getName().size() > widthName) widthName = title->getName().size();
		if (to_string(title->getTitleID()).length() > widthID) widthID = to_string(title->getTitleID()).length();
		if (numberOfPlayers > int(witdthR)) witdthR = numberOfPlayers;
		rankedList.insert(pair<int, const Title*>(numberOfPlayers, title));
	}

	widthID = rankedList.size();

	widthID += 5;
	widthName += 5;
	witdthR += 3;
	widthIn += 5;

	os << " Titles Popularity Ranking" << endl << endl;
	os << " Filters used:\n" << " Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << ", Age Group = " << ageR.minAge << " to " << ageR.maxAge << endl << endl;

	os << setw(widthIn) << "N" << setw(widthID) << "ID" << setw(widthName) << "Name" << setw(witdthR) << "Popularity" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		os << setw(widthIn) << counter << setw(widthID) << entry.second->getTitleID() << setw(widthName) << entry.second->getName() << setw(witdthR) << entry.first << endl;
		counter++;
	}
}


void GameLibrary::buildGlobalRevenueRanking(ostream & os, gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR)
{
	unsigned widthID = 3, widthName = 15, witdthR = 15, widthIn = 3;


	multimap<double, const Title*, DecrescentOrder<double>> rankedList;

	// Search for all the titles that match and organize them by revenue
	for (Title * title : titles)
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		if (!(title->getAgeRange().minAge >= ageR.minAge && title->getAgeRange().maxAge <= ageR.maxAge)) continue;
		map<Title*, double, ComparePtr<Title>>::iterator it = titlesRevenue.find(title);
		if (title->getName().size() > widthName) widthName = title->getName().size();
		if (to_string(title->getTitleID()).length() > widthID) widthID = to_string(title->getTitleID()).length();
		if (to_string((*it).second).length() > witdthR) witdthR = to_string((*it).second).length();
		rankedList.insert(pair<double, const Title*>((*it).second, title));
	}
	widthID = rankedList.size();

	widthID += 5;
	widthName += 5;
	witdthR += 3;
	widthIn += 5;

	os << " Titles Revenue Ranking" << endl << endl;
	os << " Filters used:\n" << " Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << ", Age Group = " << ageR.minAge << " to " << ageR.maxAge << endl << endl;

	os << setw(widthIn) << "N" << setw(widthID) << "ID" << setw(widthName) << "Name" << setw(witdthR) << "Revenue" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		os << setw(widthIn) << counter << setw(widthID) << entry.second->getTitleID() << setw(widthName) << entry.second->getName() << setw(witdthR) << entry.first << endl;
		counter++;
	}
}

set<Title*, ComparePtr<Title>> GameLibrary::showMatchingTitles(gameLibraryPlatform platform, gameLibraryGenre genre, ageRange ageR)
{
	set<Title*, ComparePtr<Title>> games;

	// Search for all the titles that match and organize them by revenue
	for (Title * title : titles)
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		if (!(title->getAgeRange().minAge >= ageR.minAge && title->getAgeRange().maxAge <= ageR.maxAge)) continue;
		set<Title*, ComparePtr<Title>>::iterator it = titles.find(title);
		games.insert(*it);
	}

	return games;
}

void GameLibrary::buildUserMostPlayedTitlesRanking(std::ostream & os, User * usr, gameLibraryPlatform platform, gameLibraryGenre genre)
{
	unsigned widthID = 3, widthName = 15, witdthR = 15, widthIn = 3;

	multimap<double, const Title*, DecrescentOrder<double>> rankedList;

	// Search for all the user titles that match and organize them by time played
	for (Title * title : *(usr->getPurchasedGames()))
	{
		if (!(title->getPlatform() == platform || platform == all_platforms)) continue;
		if (!(title->getGenre() == genre || genre == all_genres)) continue;
		try
		{
			double timePlayed = title->getTimePlayed(usr);
			if (title->getName().size() > widthName) widthName = title->getName().size();
			if (to_string(title->getTitleID()).length() > widthID) widthID = to_string(title->getTitleID()).length();
			if (to_string(timePlayed).length() > witdthR) witdthR = to_string(timePlayed).length();
			rankedList.insert(pair<double, const Title*>(timePlayed, title));
		}
		catch (NotOnlineTitle) { continue; }
		catch (InexistentUser) { continue; }
	}
	widthID = rankedList.size();

	widthID += 5;
	widthName += 5;
	witdthR += 3;
	widthIn += 5;

	os << " User Most Played Titles" << endl << endl;
	os << " Filters used:\n" << " Platform = " << platformEnum2string(platform);
	os << ", Genre = " << genreEnum2string(genre) << endl << endl;

	os << setw(widthIn) << "N" << setw(widthID) << "ID" << setw(widthName) << "Name" << setw(witdthR) << "Hours Played" << endl;
	int counter = 1;
	for (const auto & entry : rankedList)
	{
		os << setw(widthIn) << counter << setw(widthID) << entry.second->getTitleID() << setw(widthName) << entry.second->getName() << setw(witdthR) << entry.first << endl;
		counter++;
	}
}

double GameLibrary::averageUserTitles() const{
	double total = 0;
	for (const auto & user : users) total += user.second.size();
	if (users.size() == 0) return 0;
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
	for (const auto & user : users) total += userLibraryCost(user.first);
	if (users.size() == 0) return 0;
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
			//cout << "(" << __func__ << ") Game Library tried to get time played from Home Title " << title->getName() << endl;
			continue;
		}
		catch (InexistentUser)
		{
			//cout << "(" << __func__ << ") Tried to get time played from title " << title->getName() << " for User ";
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
		while((i = long_string.find_first_of(' ')) != string::npos) {
			result.push_back(long_string.substr(0, i));
			long_string = long_string.substr(i + 1, string::npos);
		}

		result.push_back(long_string);
	}

	return result;
}

float GameLibrary::getPurchaseChance(User * usr, Title * title)
{
	int nClicks, nSeenPromos;
	// Real Game Library should store information about user clicks and seen promo videos

	// Random float between 0 and 1
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	
	return r;
}