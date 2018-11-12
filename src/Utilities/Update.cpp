#include "Update.h"

Update::Update(Date d, std::string desc, double v) {
	date = d;
	description = desc;
	version = v;
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