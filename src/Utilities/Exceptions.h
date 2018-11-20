#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <sstream>
#include "Date.h"
#include "Update.h"

class OldUpdate
{
private:
	Update oldUpdate;
	Update currentVersion;

public:
	OldUpdate(const Update & oldUp) { oldUpdate = oldUp; };
	OldUpdate(const Update & oldUp, const Update & currUp) { oldUpdate = oldUp; currentVersion = currUp; };
	Update getOldUpdate() const { return oldUpdate; };
	Update getCurrentVersion() const { return currentVersion; };
	std::string getMessage() const
	{
		std::ostringstream oss;
		oss << oldUpdate.getVersion();
		if (currentVersion == Update())
			return "Tried to add old Update: " + oss.str();
		std::string msg = "Tried to add old Update: " + oss.str() + "while Current Version is: ";
		oss.clear();
		oss << currentVersion.getVersion();
		return msg + oss.str();

	};
};

class NotHomeTitle
{
private:
	unsigned titleID;
public:
	NotHomeTitle(unsigned id) { titleID = id; }
	unsigned getTitleID() { return titleID; }
};

class NotOnlineTitle
{
private:
	unsigned titleID;
public:
	NotOnlineTitle(unsigned id) { titleID = id; }
	unsigned getTitleID() { return titleID; }
};

class InexistentSale
{
private:
	std::string message;
	Date date;

public:
	InexistentSale() { message = "There is no existing sale!"; date = Date(); };
	InexistentSale(const Date & d1) {
		date = d1;
		std::ostringstream os;
		os << date;
		message = "There are no sales on " + os.str();
	}
	std::string getMessage() const { return message; };
	Date getDate() const { return date; };
};

// TODO: Mudar parametros??
class OverlappingSales
{
private:
	std::string message;

public:
	OverlappingSales() { message = "There are sales overlapping!"; };
	std::string getMessage() const { return message; };
};

class ExpiredSale
{
private:
	Date endSalesDate;
	Date currentDate;

public:
	ExpiredSale() { currentDate = Date::getCurrentDate(); endSalesDate = Date(); };
	ExpiredSale(Date endSalesDate) { this->endSalesDate = endSalesDate; currentDate = Date::getCurrentDate(); };
	std::string getMessage() const
	{
		std::ostringstream os1, os2;
		os1 << endSalesDate;
		os2 << currentDate;
		if (endSalesDate == Date()) return "Sale has expired: current date " + os2.str();
		return "Sale has expired: Sale ends in " + os1.str() + " and we are in " + os2.str();
	};
	Date getEndSalesDate() const { return endSalesDate; };
};

class SaleStarted
{
private:
	Date beginSalesDate;
	Date currentDate;

public:
	SaleStarted() { currentDate = Date::getCurrentDate(); beginSalesDate = Date(); };
	SaleStarted(Date beginSalesDate) { this->beginSalesDate = beginSalesDate; currentDate = Date::getCurrentDate(); };
	std::string getMessage() const
	{
		std::ostringstream os1, os2;
		os1 << beginSalesDate;
		os2 << currentDate;
		if (beginSalesDate == Date()) return "Sale has started: current date " + os2.str();
		return "Sale has started: Sale started on " + os1.str() + " and we are in " + os2.str();
	};
	Date getBeginSalesDate() const { return beginSalesDate; };
};

//TODO: generalizar??
class InvalidMonth
{
private:
	unsigned int month;

public:
	InvalidMonth() {};
	InvalidMonth(const unsigned int m) { month = m; };
	unsigned getMonth() const { return month; };
};

class InvalidDay
{
private:
	unsigned int day;

public:
	InvalidDay() {};
	InvalidDay(const unsigned int d) { day = d; };
	unsigned getDay() const { return day; };
};

class InvalidYear
{
private:
	unsigned int year;

public:
	InvalidYear() {};
	InvalidYear(const unsigned int y) { year = y; };
	unsigned getYear() const { return year; };
};

class InvalidDateFormat
{
private:
	std::string date;

public:
	InvalidDateFormat() {};
	InvalidDateFormat(const std::string d) { date = d; };
	std::string getInvalidDate() const { return date; };
};

class NegativeFunds
{
private:
	double funds;
public:
	NegativeFunds(double f) : funds(f) {}
	double getFunds() const { return funds; }
};

class NotEnoughFunds
{
private:
	double funds;
public:
	NotEnoughFunds(double f) : funds(f) {}
	double getFunds() const { return funds; }
};

class InexistentUser
{
private:
	unsigned userID;
public:
	InexistentUser(unsigned id) { userID = id; }
	unsigned getUserID() { return userID; }
};

class DuplicatedUser
{
private:
	unsigned userID;
public:
	DuplicatedUser(unsigned id) { userID = id; }
	unsigned getUserID() { return userID; }
};

class TitleUpToDate
{
private:
	unsigned titleID;
public:
	TitleUpToDate(unsigned id) { titleID = id; }
	unsigned getTitleID() { return titleID; }
};
#endif