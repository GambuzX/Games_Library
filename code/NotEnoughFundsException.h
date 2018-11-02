#ifndef NOTENOUGHFUNDSEXCEPTION_H
#define NOTENOUGHFUNDSEXCEPTION_H

class NotEnoughFundsException {

private:
	int funds;

public:
	NotEnoughFundsException();

	void getFunds();
};

#endif
