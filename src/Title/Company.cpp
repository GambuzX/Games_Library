#include <algorithm>
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

void Company::displayCompanyInfo(std::ostream &os)
{
	os << NIF << " " << name << endl;
	os << contact << endl;

	os << "Titles:" << endl;
	for (Title* title : createdTitles) {
		os << title->getTitleID() << endl;
	}
}

bool Company::addTitle(unsigned int title_id, std::set<Title *, ComparePtr<Title>> titles_set)
{
    auto it = find_if(titles_set.begin(), titles_set.end(), [title_id](const Title* title) {
        return title->getTitleID() == title_id;
    });

    if (it != titles_set.end()) {
            return addTitle(*it);
    }

    return false;
}

ostream& operator<<(ostream &out, const Company &c) {
    out << "Company Information:" << endl;
    out << "Name: " << c.getName() << endl;
    out << "NIF: " << c.getNIF() << endl;
    out << "Contact: " << c.getContact() << endl;

    for (auto it : c.getTitles()) {
      out << *it << endl;
    }

    return out;
}