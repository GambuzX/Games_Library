#ifndef COMPARE_OBJ_H
#define COMPARE_OBJ_H

/** @defgroup ComparePtr Compare Pointer
 * @{
 *
 * Template Struct for Object Pointer comparation
 * Requires definition of the operator< in the Comparable class
 * Used to mantain the order of sets and maps of Users and Titles
 * 
 * @tparam Comparable Object that we which to mantain in order
 * @see User
 * @see Title
 */
template<class Comparable>
struct ComparePtr
{
	/**
	 * @brief Overload of the operator() to allow the Pointer Object comparation
	 * 
	 * @param lhs Comparable pointer of the left side of the minor signal
	 * @param rhs Comparable pointer of the right side of the minor signal
	 * @return true If the lhs is, in fact, less than rhs
	 * @return false If the lhs is greater or equal to the rhs
	 */
	bool operator()(Comparable* lhs, Comparable* rhs) const
	{
		return *lhs < *rhs;
	}
};

/** @} */

#endif