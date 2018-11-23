#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

/** @addtogroup TitleUtility
* @{
*/

 /**
 * @brief Interface class representing a Subscription associated with an OnlineTitle
 */
class Subscription {

private:
	double subPrice; /**< @brief Subscription Price either by hour or session */

public:
	/**
	 * @brief Construct a new Subscription object
	 * Initializes the subscription price to 0
	 * 
	 */
	Subscription() { subPrice = 0; };
	/**
	 * @brief Construct a new Subscription object
	 * 
	 * @param sPrice Double that initializes the subPrice Private Member
	 */
	explicit Subscription(double sPrice) { subPrice = sPrice; };

	/**
	 * @brief Get the Subscription Price Private Member
	 * 
	 * @return double Returns the subPrice Private Member
	 */
	double getSubscriptionPrice() const { return subPrice; };

	/**
	 * @brief Virtual Function that calculates the price of the Session Played
	 * 
	 * @param sessionHours Number of hours played in that Session
	 * @return double Returns the final Session Price
	 */
	virtual double sessionPrice(double sessionHours) = 0;

	/**
	* @brief Virtual Function that tells whether a subscription is fixed or dynamic
	*
	* @return true If the Subscription is Fixed
	* @return false If the Subscription is Dynamic
	*/
	virtual bool isFixedSubscription() const = 0;
};

/** @} */

#endif
