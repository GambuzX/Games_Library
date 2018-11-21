#ifndef INPUT_H
#define INPUT_H

#include <string>
#include "..\Utilities\Date.h"
#include "..\Title\Title.h"

/**
* Robustness of the name Input:
* - Checks if the word has other characters than letters and spaces;
* - Remove spaces
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for the name
*
* @return	string			String with the name
*
* @see		removeSpace
* @see		getlineZ		(@		ConsoleFunctions)
*/
std::string nameInput(std::string question);

/**
* Robustness of the name with Numbers Input:
* - Checks if the word has other characters than letters, spaces and numbers;
* - Remove spaces
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for the name
*
* @return	string			String with the name
*
* @see		removeSpace
* @see		getlineZ		(@		ConsoleFunctions)
*/
std::string nameNumbersInput(std::string question);

/**
* Robustness of the double Input:
* - Checks if there is something left on the istringstream after the numbers
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for a double
*
* @return	double			Double with the desired number
*
* @see		afterNumber
* @see		getlineZ		(@		ConsoleFunctions)
*/
double duobleInput(std::string question);

/**
* Robustness of the int Input:
* - Checks if there is something left on the istringstream after the numbers
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for an int
*
* @return	double			Int with the desired number
*
* @see		afterNumber
* @see		getlineZ		(@		ConsoleFunctions)
*/
unsigned int intInput(std::string question);

Date dateInput(std::string question);

ageRange ageRangeInput(std::string question);

/**
* Robustness of the menu Input:
* - Checks if the input number is inside the menu option bounds
* - Controls eof character and other invalids characters erros using getlineZ;
*
* @param	question		Question that you want to write on the console when asking for the option number
* @param	inferiorLimit	Lower possible option in the menu
* @param	superiorLimit	Higher possible option in the menu
*
* @return	int				Integer with the desired option
*
* @see		getlineZ		(@		ConsoleFunctions)
*/
int menuInput(std::string question, int inferiorLimit, int superiorLimit);

#endif
