#ifndef DATE_H
#define DATE_H

class Date {

private:
	int day;
	int month;
	int year;

public:
	void getDay();

	void getMonth();

	void getYear();

	Date(int day, int month, int year);

	void operator<();

	void operator==();

	void getDate();
};

#endif
