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

#ifdef UNIX
 
#include <iostream>
#include <termios.h>
#include <unistd.h>

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
	} // GetInput ()
}
#endif