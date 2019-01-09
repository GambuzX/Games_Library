#ifndef BUY_CHANCE_H
#define BUY_CHANCE_H

#include "..\Title\Title.h"
#include "..\User\User.h"

class User;
class Title;

float sigmoid(double x);

double f(User * usr, Title * cmp);

#endif