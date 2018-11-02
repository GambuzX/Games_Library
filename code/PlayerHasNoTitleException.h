#ifndef PLAYERHASNOTITLEEXCEPTION_H
#define PLAYERHASNOTITLEEXCEPTION_H

class PlayerHasNoTitleException {

private:
	Title* title;

public:
	PlayerHasNoTitleException();

	void getTitle();
};

#endif
