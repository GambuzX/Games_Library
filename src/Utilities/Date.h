#ifndef DATE_H
#define DATE_H

#include <sstream>
#include <string>

class Date {

private:
	unsigned int day;
	unsigned int month;
	unsigned int year;

	bool LeapYear(unsigned int year) const;
	unsigned int daysInMonth(unsigned int month, unsigned int year) const;
	unsigned int daysInYear(unsigned int year) const;
	unsigned int dayNumber(unsigned int day, unsigned int month, unsigned int year) const;
	unsigned long date2days() const;
public:
	Date();
	Date(unsigned int day, unsigned int month, unsigned int year);
	Date(const Date & date);

	unsigned getDay() const { return day; };
	unsigned getMonth() const { return month; };
	unsigned getYear() const { return year; };

	void setDay(unsigned int day);
	void setMonth(unsigned int month);
	void setYear(unsigned int year);

	Date& operator=(const Date & date);
	Date operator+(unsigned int days) const;
	Date operator-(unsigned int days) const;
	long operator-(const Date & date) const;

	bool operator==(const Date& d2) const;
	bool operator<(const Date& d2) const;
	bool operator<=(const Date& d2) const;

	friend std::ostream& operator<<(std::ostream &os, const Date & date);
	friend std::istream& operator>>(std::istream &is, Date & date);

	static Date getCurrentDate();

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
	std::string date;

public:
	InvalidDateFormat() {};
	InvalidDateFormat(const std::string d) { date = d; };
	std::string getInvalidDate() const { return date; };
};

#endif
