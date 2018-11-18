#include "Session.h"

Session::Session(double duration, const Date & d) {
	sessionDuration = duration;
	date = d;
}

double Session::getSessionDuration() const {
	return sessionDuration;
}

Date Session::getDate() const {
	return date;
}

bool Session::operator<(const Session & sess2) const
{
	return date < sess2.getDate();
}
