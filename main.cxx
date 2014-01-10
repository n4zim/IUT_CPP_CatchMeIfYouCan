/*!
 *
 * \file main.cxx
 * \author Josua Gonzalez
 * \date 17/12/13
 * \brief Main file
 * \version 1
 *
 * \mainpage
 * Modified catch me if you can game
 * Remastered by your group with new rules.
 * 
 * The game plays in "real time", the objective is for one player is to catch the other
 * and is for the other player to not being caught.
 * 
 * Keys are configurable in .mapconfig
 * Maps options are configurable in .gameconfig
 *
 */

#include <time.h> 
#include <stdlib.h>

#include "globals.hxx"
#include "game.hxx" 

using namespace std;

/*!
 * \brief Program main, the program does not accept arguments.
 * \return 0
 */
int main () {
  	srand (time (NULL)); // initialise random one for all
	ChaseGame::StartGame (); // start the game
	return 0; // the end.
} // main ()