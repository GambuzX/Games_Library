#ifndef DATE_H
#define DATE_H

class Date {

private:
	unsigned int day;
	unsigned int month;
	unsigned int year;

public:
	Date(unsigned int year, unsigned int month, unsigned int day);

	void operator<<(ostream& out, const Date& d);

	void operator<<(ostream& out, const Date& d);

	void operator<<(ostream& out, const Date& d);
};

#endif
