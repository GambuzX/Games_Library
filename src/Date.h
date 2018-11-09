#ifndef DATE_H
#define DATE_H

#include <sstream>

class Date {

private:
	unsigned int day;
	unsigned int month;
	unsigned int year;

	bool LeapYear(unsigned int year) const;
	unsigned int daysInMonth(unsigned int month, unsigned int year) const;
	unsigned int daysInYear(unsigned int year) const;
	unsigned int dayNumber(unsigned int day, unsigned int month, unsigned int year) const;
public:
	Date();
	Date(unsigned int year, unsigned int month, unsigned int day);
	Date(const Date & date);

	unsigned getDay() const { return day; };
	unsigned getMonth() const { return month; };
	unsigned getYear() const { return year; };

	void setDay(unsigned int day);
	void setMonth(unsigned int month);
	void setYear(unsigned int year);

	Date& operator=(const Date &date);
	Date operator+(unsigned int days) const; // add days to date

	bool operator==(const Date& d2) const;
	bool operator<(const Date& d2) const;

	friend std::ostream& operator<<(std::ostream &os, const Date &date);
	friend std::istream& operator>>(std::istream &is, Date &date);

};

//TODO: generalizar??
class InvalidMonth {
private:
	unsigned int month;

public:
	InvalidMonth() {};
	InvalidMonth(const unsigned int m) { month = m; };
	unsigned getMonth() const { return month; };
};

class InvalidDay {
private:
	unsigned int day;

public:
	InvalidDay() {};
	InvalidDay(const unsigned int d) { day = d; };
	unsigned getDay() const { return day; };
};

class InvalidYear {
private:
	unsigned int year;

public:
	InvalidYear() {};
	InvalidYear(const unsigned int y) { year = y; };
	unsigned getYear() const { return year; };
};

class InvalidDateFormat {
private:
	string date;

public:
	InvalidDateFormat() {};
	InvalidDateFormat(const string d) { date = d; };
	string getInvalidDate() const { return dater; };
};

#endif
