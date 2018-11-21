#ifndef DYNAMICSUBSCRIPTION_H
#define DYNAMICSUBSCRIPTION_H

#include "Subscription.h"

/** @defgroup Subscription Dynamic Subscription Class
 * @{
 *
 * Dynamic Subscription Class is a derived class of the Subscription Class
 * Chargea Users Per Hour that they play an online title
 * 
 * @see Subscription
 * @see OnlineTitle
 */
class DynamicSubscription : public Subscription {


public:
	/**
	 * @brief Construct a new Dynamic Subscription object
	 * Calls the Subscription empty Constructor that initializes the subscription price to 0
	 * 
	 * @see Subscription() 
	 */
	DynamicSubscription() : Subscription() {};
	/**
	 * @brief Construct a new Dynamic Subscription object
	 * Calls the Subscription Contructor with one parameter (the subscription price)
	 * 
	 * @param sPrice Double that initializes the subPrice Private Member of the Base Class
	 * @see Subscription(double sPrice) 
	 */
    explicit DynamicSubscription(double sPrice) : Subscription(sPrice) {};

	/**
	 * @brief Function that calculates the price of the Session Played
	 * 
	 * @param sessionHours Number of hours played in that Session
	 * @return double Returns the final Session Price
	 */
	double sessionPrice(double sessionHours) override
    { return sessionHours * getSubscriptionPrice(); };

	/**
	* @brief Virtual Function that tells whether a subscription is fixed or dynamic
	*
	* @return true If the Subscription is Fixed
	* @return false If the Subscription is Dynamic
	*/
	bool isFixedSubscription() const override
    { return false; };
};

/** @} */

#endif
