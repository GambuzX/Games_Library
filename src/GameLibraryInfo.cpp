#include "GameLibraryInfo.h"

using namespace std;

string platformEnum2string(gameLibraryPlatform platform)
{
	switch (platform)
	{
	case pc: return "PC";
	case ps4: return "PS4";
	case xbox: return "XBOX";
	}
	// TODO CHANGE THIS???
	return "Invalid platform";
}

string genreEnum2string(gameLibraryGenre genre)
{
	switch (genre)
	{
	case action: return "Action";
	case adventure: return "Adventure";
	case puzzle: return "Puzzle";
	case shooter: return "Shooter";
	case simulation: return "Simulation";
	case rpg: return "RPG";
	case platformer: return "Platformer";
	case strategy: return "Strategy";
	case sports: return "Sports";
	case mmo: return "MMO";
	case all_genres: return "All Genres";
	}
	// TODO CHANGE THIS???
	return "Invalid genre";
}