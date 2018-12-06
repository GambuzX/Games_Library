#ifndef COMPANY_H
#define COMPANY_H

#include <set>
#include <string>
#include "Title.h"
#include "..\Utilities\CompareObj.h"

typedef std::set<Title*, ComparePtr<Title>> titleSet;

class Company
{
private:
	titleSet createdTitles;
	std::string name;
	int NIF;
	int contact;

public:
	Company(std::string n, int nif, int cont) : name(n), NIF(nif), contact(cont) {}
	bool addTitle(Title * title);
};

#endif
