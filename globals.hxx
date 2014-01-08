/*!
 *
 * \file globals.hxx
 * \author Josua Gonzalez
 * \date 07/01/14
 * \brief Defines global constants and variables for the ChaseGame namespace
 * \version 1
 *
 * Contains constants and structs used in the game code
 * 
 */


#ifndef globals_h 
#define globals_h

#define UNIX
#include "windows.hxx" 
#include "unix.hxx"
#include <vector> 
#include <string> 

namespace ChaseGame {
	typedef std::vector<char> CVLine;
	typedef std::vector<CVLine> CMatrix;
	typedef std::pair<unsigned, unsigned> CPosition; // x, y

	// Color value are defined in windows or unix

	//! Character representing player one
	const char KTokenPlayer1 = 'X';
	
	//! Color value representing player one
	const int KColTokenP1 = CLR_RED;
	
	//! Character representing player two
	const char KTokenPlayer2 = 'O';
	
	//! Color value representing player two
	const int KColTokenP2 = CLR_BLUE;
	
	//! Character representing voidness
	const char KEmpty = '.';

	//! Obstacles in the game
	const char KObstacle = '#';

	//! Defines a position
	struct SPlayerPos
	{
		//! X position
		unsigned X = 0;
		//! Y position
		unsigned Y = 0;
		bool operator==(const SPlayerPos& objet) {
		    return (X == objet.X) && (Y == objet.Y);
		}
	};

	//! Contains all the map generation parameters
	struct SMapGenParams {
		//! Number of lines a map contains
		unsigned MapHeight = 10;
		//! Number of columns a map contains
		unsigned MapWidth = 30;
		//! Position of player one
		SPlayerPos PosPlayer1;
		//! Position of player two
		SPlayerPos PosPlayer2;
	};

	//! Player specific keys
	struct SPlayerKeys {
		//! Up keycode
		wchar_t Up;
		//! Down keycode
		wchar_t Down;
		//! Left keycode
		wchar_t Left;
		//! Right keycode
		wchar_t Right;
	};

	//! Player state
	struct SPlayerState {
		//! Can a player bypass wall collision check ?
		bool CanPassThroughWalls;
		//! Player position
		SPlayerPos Position;
		//! Keys specific to player
		SPlayerKeys Keys;
	};

	struct SGameStatusDisplay {
		int Time;
		int PlayerChasing;
	};

	//! Contains game configuration
	struct SGameStatus {
		//! Key to pause the game
		char KeyPause;
		//! Key to exit the game
		char KeyExit;
		//! Player one status
		SPlayerState P1;
		//! Player two status
		SPlayerState P2;
		//! Game lang
		std::string Lang;

		int Timer;

		int PlayerChasing;

		int Round; 


	};
}

#endif
