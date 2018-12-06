#include "Company.h"

using namespace std;

bool Company::addTitle(Title * title)
{
	pair<titleSet::const_iterator, bool> it = createdTitles.insert(title);
	return it.second;
}