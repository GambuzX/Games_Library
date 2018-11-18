#include "HomeTitle.h"
#include "..\Utilities\Exceptions.h"

using namespace std;

HomeTitle::HomeTitle(string name, double price, Date releaseDate, ageRange ageR, string platform, string genre, string company) : Title(name, price, releaseDate, ageR, platform, genre, company) 
{
	titleUpdateHistory.push_back(Update(releaseDate));
}

void HomeTitle::addNewUser(User & u)
{
	map<User*, vector<Update>, ComparePtr<User>>::iterator it;
	it = userUpdates.find(&u);
	if (it != userUpdates.end())
		throw DuplicatetUser(u.getUserID());
	
	vector<Update> v1;
	v1.push_back(getCurrentVersion());
	userUpdates.insert(pair<User*, vector<Update>>(&u, v1));
}

void HomeTitle::updateTitle(Update * newUpdate)
{
	if (titleUpdateHistory.size() == 0)
		titleUpdateHistory.push_back(*newUpdate);
	else if (getCurrentVersion() < *newUpdate)
		titleUpdateHistory.push_back(*newUpdate);
	else
		throw OldUpdate(*newUpdate, getCurrentVersion());
}

void HomeTitle::updateUserVersion(const User & u)
{
	map<User*, vector<Update>, ComparePtr<User>>::iterator it;
	it = userUpdates.find(const_cast<User*>(&u));

	if (it == userUpdates.end())
		throw InexistentUser(u.getUserID());
	// Verificar se é a versão atual
	else if (getCurrentUserVersion(u) == getCurrentVersion())
		throw TitleUpToDate(getTitleID());
	it->second.push_back(getCurrentVersion());
}

void HomeTitle::updateUserVersion(unsigned int userID)
{
	for (auto & pair : userUpdates)
		if (pair.first->getUserID() == userID) {
			if (getCurrentUserVersion(userID) == getCurrentVersion())
				throw TitleUpToDate(userID);
			pair.second.push_back( getCurrentVersion() );
			return;
		}
	throw InexistentUser(userID);
}

/*
void HomeTitle::updateUserVersion(std::string name)
{
	for (auto & pair : userUpdates)
		if (pair.first->getName() == name)
			pair.second = getCurrentVersion();
	//TODO: Add exception
	throw;
}
*/

double HomeTitle::getStats() const {
	throw NotOnlineTitle(getTitleID());
}

const Update & HomeTitle::getCurrentUserVersion(const User & u) const
{
	map<User*, vector<Update>, ComparePtr<User>>::const_iterator it;
	it = userUpdates.find(const_cast<User*>(&u) );

	if (it == userUpdates.end())
		throw InexistentUser(u.getUserID());
	return it->second.at(userUpdates.size() - 1);
}

const Update & HomeTitle::getCurrentUserVersion(unsigned int userID) const
{
	for (auto & pair : userUpdates)
		if (pair.first->getUserID() == userID)
			return	pair.second.at(userUpdates.size() - 1);
	throw InexistentUser(userID);
}

/*
const Update & HomeTitle::getCurrentUserVersion(std::string name) const
{
	for (auto & pair : userUpdates)
		if (pair.first->getName() == name)
			return	pair.second;	
	//TODO: Add exception
	throw;
}
*/

bool HomeTitle::operator<(const Title & t2) const
{
	return getTitleID() < t2.getTitleID();
}