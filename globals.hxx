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

/*! \namespace ChaseGame
 * Project namespace for the game
 */
namespace ChaseGame {
	//! Matrix line type
	typedef std::vector<char> CVLine;
	//! Matrix type
	typedef std::vector<CVLine> CMatrix;

	// Color value are defined in windows.hxx or unix.hxx

	//! Language codes
	enum Langs { LANG_FR, LANG_EN, LANG_ES };

	//! Difficulty levels
	enum DifficultyLevels { DIFFLVL_EASY, DIFFLVL_NORM, DIFFLVL_HARD, DIFFLVL_CRZY};

	//! Character representing player one
	const char KTokenPlayer1 = 'X';
	
	//! Character representing player two
	const char KTokenPlayer2 = 'O';
	
	//! Character representing voidness
	const char KEmpty = ' ';

	//! Character representing obstacles and walls
	const char KObstacle = '#';

	//! Character sent when a move is not allowed
	const char KCancelled = '0';

	//! Defines a position
	struct SPlayerPos
	{
		//! X position
		unsigned X = 0;
		//! Y position
		unsigned Y = 0;
		//! Allow the comparison between to SPlayerPos
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
		//! Player score
		int Score;
		//! Player role : chasing or being chased
		bool IsChasing;
	};

	//! Color set to use when displaying the map
	struct SColorSet {
		//! Color value representing player one
		int ColorP1;		
		//! Color value representing player two
		int ColorP2;		
		//! Color value representing an obstacle
		int ColorObstacle;
		//! Color value representing a wall
		int ColorWall; 
		//! Color value representing a bonus
		int ColorBonus;
		//! Color value representing a malus 
		int ColorMalus; 
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
		//! Colors to use
		SColorSet ColorSet;
		//! Round
		int Round;
		//! Game lang
		int Lang;
	};
}

#endif
