#include "Date.h"
#include "Exceptions.h"
#include <string>
#include <chrono>

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
	default:
		break;
	}
	// RETURN SOMETHING TO REMOVE WARNING
	return 0;
}

unsigned int Date::daysInYear(unsigned int year) const
{
	return (LeapYear(year) ? 366 : 365);
}

unsigned int Date::dayNumber(unsigned int day, unsigned int month, unsigned int year) const
{
	unsigned int res = day;

	for (unsigned int m = 1; m < month; m++)
		res += daysInMonth(m, year);

	return res;
}

unsigned long Date::date2days() const
{
	unsigned long res = 0;
	
	for (unsigned int y = 0; y < this->year; y++)
		res += daysInYear(y);

	return res + dayNumber(this->day, this->month, this->year);
}

Date::Date()
{
	day = 1;
	month = 1;
	year = 0;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
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

Date Date::operator-(unsigned int days) const
{
	Date res(*this);
	
	while (days > daysInYear(res.year)) {
		days -= daysInYear(res.year - 1);
		res.year--;
	}

	unsigned pres = dayNumber(res.day, res.month, res.year);

	if (days >= pres){
		res.year--;
		days = daysInYear(res.year) - days + pres;
	}
	else {
		days = pres - days;
	}

	res.month = 1;

	while (days > daysInMonth(res.month, res.year)) {
		days -= daysInMonth(res.month, res.year);
		res.month++;
	}

	res.day = days;
	
	return res;
}

long Date::operator-(const Date & date) const
{
	return this->date2days() - date.date2days();
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

bool Date::operator<=(const Date & d2) const
{
	return (*this) < d2 || (*this) == d2;
}

ostream & operator<<(ostream & os, const Date & date)
{
	os << (date.getDay() > 9 ? "" : "0");
	os << date.getDay() << "/";
	os << (date.getMonth() > 9 ? "" : "0");
	os << date.getMonth() << "/" << date.getYear();
	return os;
}

istream & operator>>(istream & is, Date & date)
{

	char c1, c2;
	unsigned int d, m, y;
	
	is >> d >> c1 >> m >> c2 >> y;
	
	if (c1 != c2){
		string invalidDate = to_string(d) + c1 + to_string(m) + c2 + to_string(y);
		throw InvalidDateFormat(invalidDate);
	}

	date = Date(d, m, y);

	return is;
}

Date Date::getCurrentDate()
{
	time_t theTime = time(nullptr);
	struct tm *aTime = localtime(&theTime);

	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime->tm_year + 1900; // Year is # years since 1900

	return Date(day, month, year);
}