#include "Update.h"

Update::Update(Date d, std::string desc, double v, double updatePrice) {
	date = d;
	description = desc;
	version = v;
	updateCost = updatePrice;
}

Date Update::getDate() const {
	return date;
}

std::string Update::getDescription() const {
	return description;
}

double Update::getVersion() const {
	return version;
}


bool Update::operator==(const Update & update) const {
	return update.getVersion() == version;
}

bool Update::operator<(const Update & update) const {
	return version < update.getVersion();
}

std::ostream &operator<<(std::ostream &os, const Update &update)
{
	os << update.getDate() << " " << update.getDescription() << std::endl;
	os << update.getVersion() << " " << update.getUpdatePrice() << std::endl;
    return os;
}
