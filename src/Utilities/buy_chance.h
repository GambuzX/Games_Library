#include <cmath>
#include <set>
#include "..\Title\Title.h"
#include "..\User\User.h"
#include "..\GameLibrary.h"

const double EULER_CONSTANT = std::exp(1.0);
const double SIMILAR_GAMES_WEIGHT = 4;
const double FRIENDS_WEIGHT = 1;
const double ADS_WEIGHT = 2;
const double SEARCHES_WEIGHT = 2;

double sigmoid(double x)
{
	return 1 / (1 + pow(EULER_CONSTANT / 2.5, -26 - x));
}

double f(User * usr, Title * cmp)
{
	const std::set<Title*, ComparePtr<Title>>* user_games = usr->getPurchasedGames();
	std::set<Title*, ComparePtr<Title>>::iterator it;

	/* Similarity in games */
	double games_points = 0;
	for (it = user_games->begin(); it != user_games->end(); it++)
	{
		int points = 0;
		if (cmp->getGenre() == (*it)->getGenre()) points++;
		if (cmp->getCompany() == (*it)->getCompany()) points++;
		if (cmp->getPlatform() == (*it)->getPlatform()) points++;
		if (GameLibrary::isOnlineTitle(cmp) == GameLibrary::isOnlineTitle((*it))) points++;
		games_points += points;
	}

	/* Friends with games */
	int friends_with_game = 0;
	std::set<User*, ComparePtr<User>>::iterator it2;
	for (it2 = usr->getFriendsList().begin(); it2 != usr->getFriendsList().end(); it2++)
		if ((*it2)->hasTitle(cmp)) friends_with_game++;

	/* Clicks and ads */
	unsigned int searches = usr->getNumberOfSearches(cmp);
	unsigned int ads = usr->getNumberOfSeenAds(cmp);

	return SIMILAR_GAMES_WEIGHT * games_points + FRIENDS_WEIGHT * friends_with_game + ADS_WEIGHT * ads + SEARCHES_WEIGHT * searches;
}
