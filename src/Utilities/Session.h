#ifndef SESSION_H
#define SESSION_H

#include "Date.h"

/** @defgroup Seesion Session Class
 * @{
 *
 * Session Class representing the time played and the date when an online Game is played
 * @see OnlineTitle
 * @see Date
 */
class Session {

private:
	double sessionDuration;	/**< @brief Duration in hours of a playing session */
	Date date;	/**< @brief Date corresponding to when the session was played */

public:
	
	/**
 	* @brief Construct a new Session object
 	* 
 	* @param duration Time, in hours, to be saved in sessionDuration
 	* @param d Date when the game was played, to be saved in date
 	*/
	Session (double duration, const Date & d);

	/**
	 * @brief Get the Session Duration Private Member
	 * 
	 * @return double Returns Session Duration Private Member
	 */
	double getSessionDuration() const;
	/**
	 * @brief Get the Date Private Member
	 * 
	 * @return Date Returns Date Private Member
	 */
	Date getDate() const;

	/**
	* @brief Overload of less than operator
	* One Session is "less" than other if it is played in a previous date
	*
	* @param sess2 Session with which we are comparing the "Current" Session
	* @return true If the Session was played before sess2 (right hand side of the signal)
	* @return false If the Session was played after or on the same day as sess2 (right hand side of the signal)
	*/
	bool operator<(const Session & sess2) const;
};

/** @} */

#endif
