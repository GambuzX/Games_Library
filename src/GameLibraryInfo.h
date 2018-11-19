#ifndef GAME_LIBRARY_INFO
#define GAME_LIBRARY_INFO

/**
* @brief Enumerated type for identifying the different genres of the Game Library's Titles
*/
enum gameLibraryGenre
{
	all_genres,
	action, /*!< Action genre*/
	adventure, /*!< Adventure genre*/
	puzzle, /*!< Puzzle genre*/
	shooter, /*!< First Person Shooter genre*/
	simulation, /*!< Simulation genre*/
	rpg, /*!< Role Playing Game genre*/
	platformer, /*!< Platformer genre*/
	strategy, /*!< Strategy genre*/
	sports, /*!< Sports genre*/
	mmo /*!< MMO genre*/
};

/**
* @brief Enumerated type for identifying the different platforms the Game Library supports
*/
enum gameLibraryPlatform
{
	all_platforms,
	pc, /*!< Personal Computer */
	ps4, /*!< Playstation 4 */
	xbox, /*!< X-Box */
	all
};

/**
* @brief Enumerated type for identifying the different filters to be used when building the consuming habits list
*/
enum ConsumingHabitsFilter
{
	pus, /*!< Purchases, Updates and Subscriptions */
	p, /*!< Purchases */
	u, /*!< Updates */
	s, /*!< Subscriptions */
	pu, /*!< Purchases and Updates */
	ps, /*!< Purchases and Subscriptions */
	us /*!< Updates and Subscriptions */
};


#endif