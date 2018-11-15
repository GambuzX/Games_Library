#ifndef SESSION_H
#define SESSION_H

#include "Date.h"

class Session {

private:
	double sessionDuration;
	Date date;

public:
	Session (double duration, const Date & d);
	double getSessionDuration() const;
	Date getDate() const;
};

#endif
