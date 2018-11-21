#ifndef FIXEDSUBSCRIPTION_H
#define FIXEDSUBSCRIPTION_H

#include "Subscription.h"

/** @defgroup Subscription Fixed Subscription Class
 * @{
 *
 * Fixed Subscription Class is a derived class of the Subscription Class
 * Charges Users Per Session that they play an online title
 * 
 * @see Subscription
 * @see OnlineTitle
 */
class FixedSubscription : public Subscription {

public:
	/**
	 * @brief Construct a new Fixed Subscription object
	 * Calls the Subscription empty Constructor that initializes the subscription price to 0
	 * 
	 * @see Subscription() 
	 */
	FixedSubscription() : Subscription() {};
	/**
	 * @brief Construct a new Fixed Subscription object
	 * Calls the Subscription Contructor with one parameter (the subscription price)
	 * 
	 * @param sPrice Double that initializes the subPrice Private Member of the Base Class
	 * @see Subscription(double sPrice) 
	 */
	FixedSubscription(double sPrice) : Subscription(sPrice) {};

	/**
	 * @brief Function that calculates the price of the Session Played
	 * 
	 * @param sessionHours Number of hours played in that Session
	 * @return double Returns the final Session Price
	 */
	double sessionPrice(double sessionHours) { return getSubscriptionPrice(); };

	/**
	* @brief Virtual Function that tells whether a subscription is fixed or dynamic
	*
	* @return true If the Subscription is Fixed
	* @return false If the Subscription is Dynamic
	*/
	bool isFixedSubscription() const { return true; };
};

/** @} */

#endif
