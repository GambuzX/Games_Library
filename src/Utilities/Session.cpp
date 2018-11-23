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

std::ostream &operator<<(std::ostream &os, const Session &session)
{
	os << session.getDate() << " " << session.getSessionDuration() << std::endl;
    return os;
}
