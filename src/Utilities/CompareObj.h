#ifndef COMPARE_OBJ_H
#define COMPARE_OBJ_H

#include "..\User\User.h"
#include "..\Title\Title.h"

struct CompareUserPtr
{
	bool operator()(const User * usr1, const User * usr2) const { return usr1->getUserID() < usr2->getUserID(); }
};

struct CompareTitlePtr
{
	bool operator()(const Title * t1, const Title * t2) const	{ return t1->getTitleID() < t2->getTitleID(); }
};

#endif