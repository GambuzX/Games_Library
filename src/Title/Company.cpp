#include "Company.h"

using namespace std;

bool Company::addTitle(Title * title)
{
	pair<titleSet::const_iterator, bool> it = createdTitles.insert(title);
	return it.second;
}

bool Company::removeTitle(Title * title)
{
	titleSet::iterator it = createdTitles.find(title);
	if (it == createdTitles.end()) return false;
	createdTitles.erase(it);
	return true;
}