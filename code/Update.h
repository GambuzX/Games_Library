#ifndef UPDATE_H
#define UPDATE_H

class Update {

private:
	Date date;
	String description;
	int version;

public:
	void getDate();

	void getDescription();

	Update();

	void getVersion();
};

#endif
