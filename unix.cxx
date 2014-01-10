/*!
 *
 * \file unix.cxx
 * \author Josua Gonzalez
 * \date 07/01/14
 * \brief Defines unix-only functions
 * \version 1
 *
 * Defines unix-only functions
 * 
 */

#include "globals.hxx"
#include "unix.hxx"
 
#include <iostream>
#include <limits>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>


using namespace std;

namespace ChaseGame {
	void ClearScreen ()	{
		cout << "\033[H\033[2J";
	} // ClearScreen ()

	void Color (const int & Color) {
	    cout << "\033[" << Color <<"m";
	} // Color ()

	void BackgroundColor (const int & Color) {
	    cout << "\033[" << Color + 10 <<"m";
	} // BackgroundColor ()


	char GetInput () {
		/*// We only want one NEW char so we clear the cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(!cin) {
            cin.clear();
        }*/

		//*
		// Adapted from http://stackoverflow.com/questions/1798511/how-to-avoid-press-enter-with-any-getchar/1798833#1798833
		char input;   
	    static struct termios oldt, newt;

	    // save old terminal settings
	    tcgetattr (STDIN_FILENO, &oldt);
	    newt = oldt;

	    // Disabling ICANON and ECHO flags to disable validation and input echo
	    newt.c_lflag &= ~(ICANON | ECHO);          

	    // apply new terminal settings
	    tcsetattr (STDIN_FILENO, TCSANOW, &newt);

	    input = getchar ();
		
		if(input == 27) { // bugfix for arrow sequence sending escape
			input = getchar ();
			/*if(input == 91) {
				input = getchar ();
			}*/
		}

	    if(!cin) {
            cin.clear();
        }


	    // restore old terminal settings
	    tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
	    //if(input == char(27))
	    //	return char(42);
		return input; //*/
		//return ' ';
	} // GetInput ()

	void Sleep (int USec) {
		usleep(USec);
	} // Sleep ()

	void Pause () {
		Color(CLR_RESET);

		cout << "\n\n\nPress enter to continue";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(!cin) {
            cin.clear();
        }
	} // Pause ()

}