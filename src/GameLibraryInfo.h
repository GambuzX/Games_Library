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
	fps, /*!< First Person Shooter genre*/
	simulation, /*!< Simulation genre*/
	rpg, /*!< Role Playing Game genre*/
	platformer /*!< Platformer genre*/
};

/**
* @brief Enumerated type for identifying the different age groups defined by the Game Library
*/
enum gameLibraryAgeGroup
{
	// TODO CHANGE THIS!!!
	all_ages,
	a_0_12,
	a_13_17,
	a_18_29,
	a_30_50,
	a_50_plus
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


#endif