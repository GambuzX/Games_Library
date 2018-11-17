#ifndef COMPARE_OBJ_H
#define COMPARE_OBJ_H

#include "..\User\User.h"
#include "..\Title\Title.h"

template<class Comparable>
struct ComparePtr
{
	bool operator()(Comparable* lhs, Comparable* rhs) const
	{
		return *lhs < *rhs;
	}
};

#endif