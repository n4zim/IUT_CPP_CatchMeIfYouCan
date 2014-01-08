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

#ifdef UNIX
 
#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;

/*! \namespace SuperGame
 * Project namespace for the game
 */
namespace ChaseGame {
	void ClearScreen ()	{
		cout << "\033[H\033[2J";
	}

	void Color (const int & coul) {
	    cout << "\033[" << coul <<"m";
	}

	void BackgroundColor (const int & coul) {
	    cout << "\033[" << coul + 10 <<"m";
	}


	char GetInput () {
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
	    
	    // restore old terminal settings
	    tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

		return input;
	}
}
#endif