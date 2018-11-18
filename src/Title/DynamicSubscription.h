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
class DynamicSubscription : Subscription {


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
	DynamicSubscription(double sPrice) : Subscription(sPrice) {};

	/**
	 * @brief Function that calculates the price of the Session Played
	 * 
	 * @param sessionHours Number of hours played in that Session
	 * @return double Returns the final Session Price
	 */
	double sessionPrice(double sessionHours) { return sessionHours * getSubscriptionPrice(); };
};

/** @} */

#endif
