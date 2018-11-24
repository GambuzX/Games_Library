#ifndef COMPARE_OBJ_H
#define COMPARE_OBJ_H

/** @addtogroup GameLibrary
 * @{
 */

/**
 * @brief Comparable class used to order pointers by comparing the pointed elements
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

/**
* @brief Comparable class used to order elements by Decrescent order
*/
template<class Comparable>
struct DecrescentOrder
{
	/**
	* @brief Overload of the operator() to allow the Pointer Object comparation
	*
	* @param lhs Comparable pointer of the left side of the minor signal
	* @param rhs Comparable pointer of the right side of the minor signal
	* @return true If the lhs is, in fact, less than rhs
	* @return false If the lhs is greater or equal to the rhs
	*/
	bool operator()(Comparable lhs, Comparable rhs) const
	{
		return lhs > rhs;
	}
};

/** @} */

#endif