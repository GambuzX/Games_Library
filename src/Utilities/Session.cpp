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