#ifndef UPDATE_H
#define UPDATE_H

#include "Date.h"
#include <string>

class Update {

private:
	Date date;
	std::string description;
	double version;
public:
	Update(Date d, string desc, double v);
	Date getDate() const;
	std::string getDescription() const;
	double getVersion() const;

	bool operator==(const Update & update) const;
	bool operator<(const Update & update) const;
};

#endif
