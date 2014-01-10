/*!
 *
 * \file game.hxx
 * \author 
 * \date 09/01/14
 * \brief game.cxx function prototypes
 * \version 1 
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <time.h> 
#include <stdlib.h>

#include "globals.hxx"
#include "windows.hxx" 
#include "unix.hxx" 
#include "file.hxx" 
#include "map.hxx" 

#ifndef game_h 
#define game_h

using namespace std;

namespace ChaseGame {

	/*!
	 * \brief Processes user input
	 * \param Mat Game Matrix
	 * \param Input input given
	 * \param Config Game configuration
	 * \return Chararcter representing the replaced charachter while moving
	 * \return KCancelled if the move was cancelled
	 */
	char ProcessInput(CMatrix& Mat, const char Input, SGameStatus& Config);
	
	/*!
	 * \brief This is the game loop
	 * \param Mat Game Matrix
	 * \param MapGenParams Map generator parameters
	 * \param Config Game configuration
	 * \return true If game is running
	 * \return false If game is ended
	 */
	bool GameLoop (CMatrix& Mat, SMapGenParams& MapGenParams, SGameStatus& Config);

	/*!
	 * \brief This function starts the game
	 */
	void StartGame ();

}

#endif