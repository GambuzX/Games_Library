#include "Date.h"

using namespace std;

bool Date::LeapYear(unsigned int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned int Date::daysInMonth(unsigned int month, unsigned int year) const
{
	if (month > 12)
		throw InvalidMonth(month);
	switch (month) {
	case 1: // january
	case 3: // march
	case 5: // may
	case 7: // july
	case 8: // august
	case 10: // october
	case 12: // december
		return 31;

	case 4: // april
	case 6: // june
	case 9: // september
	case 11: // november
		return 30;

	case 2: // february
		return LeapYear(year) ? 29 : 28;
	}
}

unsigned int Date::daysInYear(unsigned int year) const
{
	return LeapYear(year) ? 366 : 365;
}

unsigned int Date::dayNumber(unsigned int day, unsigned int month, unsigned int year) const
{
	unsigned int res = day;

	for (unsigned int m = 1; m < month; m++)
		res += daysInMonth(m, year);

	return res;
}

Date::Date()
{
	day = 1;
	month = 1;
	year = 0;
}

Date::Date(unsigned int year, unsigned int month, unsigned int day) {
	if (month > 12)
		throw InvalidMonth(month);
	if (day > daysInMonth(month, year))
		throw InvalidDay(day);
	
	this->day = day;
	this->month = month;
	this->year = year;
}

Date::Date(const Date & date)
{
	day = date.getDay();
	month = date.getMonth();
	year = date.getYear();
}

void Date::setDay(unsigned int day)
{
	if (day > daysInMonth(month, year))
		throw InvalidDay(day);

	this->day = day;
}

void Date::setMonth(unsigned int month)
{
	if (month > 12)
		throw InvalidMonth(month);
	if (day > daysInMonth(month, year))
		throw InvalidMonth(month);
	this->month = month;
}

void Date::setYear(unsigned int year)
{
	if (day > daysInMonth(month, year))
		throw InvalidYear(year);
	this->year = year;
}

Date& Date::operator=(const Date &date) {
	if (&date != this) {
		day = date.getDay();
		month = date.getMonth();
		year = date.getYear();
	}

	return *this;
}

Date Date::operator+(unsigned int days) const {
	Date res(*this);

	days += dayNumber(res.day, res.month, res.year);

	while (days > daysInYear(res.year)) {
		days -= daysInYear(res.year);
		res.year++;
	}

	res.month = 1;

	while (days > daysInMonth(res.month, res.year)) {
		days -= daysInMonth(res.month, res.year);
		res.month++;
	}

	res.day = days;

	return res;
}

bool Date::operator==(const Date & d2) const
{
	return year == d2.getYear() && month == d2.getMonth() && day == d2.getDay();
}

bool Date::operator<(const Date & d2) const
{
	if (year != d2.getYear())
		return year < d2.getYear();

	else if (month != d2.getMonth())
		return month < d2.getMonth();

	return day < d2.getDay();
}

ostream & operator<<(ostream & os, const Date & date)
{
	os << date.getDay() << "/";
	os << (date.getMonth() > 10 ? "" : "0");
	os << date.getMonth() << "/" << date.getYear();
	return os;
}

istream & operator>>(istream & is, Date & date)
{
	istream is2 = is;
	string invalidDate(istreambuf_iterator<char>(is2), {})
	char c1, c2;
	unsigned int d, m, y;
	
	is >> d >> c1 >> m >> c2 >> y;
	
	if (c1 != c2)
		throw InvalidDateFormat(invalidDate);
	date = Date(d, m, y);
}
