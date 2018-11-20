#ifndef ConsoleFunctions_h
#define ConsoleFunctions_h

#include <windows.h>
#include <iostream>

//using namespace std;

/**
 * Sets the Color of the console Text
 * 
 * @param    color              Unsigned integer code of the desired color
 */
void setcolor(unsigned int color);

/**
 * Sets the Color of the console Text and its background
 * Background color it's only possible to change from black to gray and back
 * 
 * @param   color               Unsigned integer code of the desired text color
 * @param   background_color    Unsigned integer code correspondent to any color
 */
void setcolor(unsigned int color, unsigned int background_color);

/**
 * Gets the width of the console and makes a line all the way across it with a certain character
 * 
 * @param   lineChar            Character you want to write across the console
 */
void lineAcrossConsole(char lineChar);

/**
 * Writes a certain word in the center of the console
 * 
 * @param   title               String to be written centered in the console 
 */
void centerWord(std::string title);

/**
 * Clears the console screen from a certain point forward
 * 
 * @param   coordScreen         Coordinates from where you want to begin erasing the screen
 */
void clrscr(COORD coordScreen);

/**
 * Gets the coordinates of the current position of the cursor in the console
 * 
 * @param   hConsoleOutput      Handle for the Console
 * 
 * @return  COORD               Returns the position of the cursor in the console
 */
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

/**
 * Getline Method improved that doesn't crash when you press Ctrl+Z in the middle of the input
 * 
 * Due to an error in the Windows implementation of the getline method when you write Ctrl+Z
 * in the middle of the string input you need to press Enter two times. This method corrects this.
 * 
 * @param   stream              Input Stream that you want to input from (method improved for cin)
 * @param   str                 String variable where the inputted string will be saved
 * 
 * @return  istream             Returns the state of the input string chosen so that you can test whether istream.fail occurred
 */
std::istream& getlineZ(std::istream& stream, std::string& str);

#endif