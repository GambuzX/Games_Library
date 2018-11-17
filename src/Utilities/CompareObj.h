#ifndef COMPARE_OBJ_H
#define COMPARE_OBJ_H

/*
struct CompareUserPtr
{
	bool operator()(const User * usr1, const User * usr2) const { return *usr1 < *usr2; }
};

struct CompareTitlePtr
{
	bool operator()(const Title * t1, const Title * t2) const	{ return *t1 < *t2; }
};
*/
template<class Comparable> 
struct ComparePtr {
	bool operator()(Comparable* lhs, Comparable* rhs) const {
		return *lhs < *rhs;
	}
};

#endif