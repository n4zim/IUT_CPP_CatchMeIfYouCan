/*!
 *
 * \file globals.hxx
 * \author Peanut Butter Team
 * \date 07/01/14
 * \brief Defines global constants and variables for the ChaseGame namespace
 * \version 1
 *
 * Contains constants and structs used in the game code
 * 
 */


#ifndef globals_h 
#define globals_h

//#define UNIX
#include "unix.hxx"
#include <vector> 
#include <string> 

/*! \namespace ChaseGame
 * \brief Main namespace
 * Project namespace for the game
 * Contains all the funcitons, structs, enums and constansts related to the game
 */
namespace ChaseGame {
	//! Matrix line type
	typedef std::vector<char> CVLine;

	//! Matrix type
	typedef std::vector<CVLine> CMatrix;

	//! Language codes
	enum Langs { LANG_FR, LANG_EN, LANG_ES };

	//! Difficulty levels
	enum DifficultyLevels { DIFFLVL_EASY=0, DIFFLVL_NORM=1, DIFFLVL_HARD=2, DIFFLVL_CRZY=3 };

	//! Unix color values
	enum ConsoleColors { CLR_BLACK=30, CLR_RED=31, CLR_GREEN=32, CLR_YELLOW=33, CLR_BLUE=34, CLR_MAGENTA=35, CLR_CYAN=36, CLR_WHITE=37, CLR_GREY=30, CLR_RESET=0 };

	//! Music state, the value changes the music tracks being played.
	enum GameMusicState { GMS_TITLE, GMS_STARTING, GMS_INGAME, GMS_STOP };

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

	//! Character sent when the user wants to exit the game (escape)
	const char KExit = 'Q';

	//! Character representing bonuses
	const char KBonus = '@';
	
	//! Character representing maluses
	const char KMalus = '$';

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
		unsigned Score;
		//! Player role : chasing or being chased
		bool IsChasing;
		//! If the player is stunned
		bool IsStunned = false;
		//! Duration of stun
		unsigned StunDuration;
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

	//! Localised strings
	struct SLangStrings {
		//! Label : play game
		std::string TitlePlayGameLabel    = "TYPE 'PLAY' TO START PLAYING OR...      ";
		//! Label : configure game
		std::string TitleGameOptionsLabel = "TYPE 'OPTIONS' TO CONFIGURE STUFF UP!   ";
		//! Label : direction up
		std::string DirUp = "UP";
		//! Label : direction down
		std::string DirLeft = "DOWN";
		//! Label : direction left
		std::string DirDown = "LEFT";
		//! Label : direction right
		std::string DirRight = "RIGHT";
		//! Label : mini game rule line 1
		std::string TitleMGRL1 = "  ONE PLAYER  ";
		//! Label : mini game rule line 4
		std::string TitleMGRL2 = " HAS TO CATCH ";
		//! Label : mini game rule line 3
		std::string TitleMGRL3 = "   THE OTHER  ";
		//! Label : player 1 (exacty 11 chars)
		std::string TitlePlayer1 = "...PLAYER1...";
		//! Label : player 2 (exacty 11 chars)
		std::string TitlePlayer2 = "...PLAYER2...";
		//! Label : rules (exacty 12 chars)
		std::string TitleRules = "....RULES...";
		//! Label : shown when tie
		std::string MsgTie = "\n  TIE !\n Now starting a new round to know who the real winner is...";
		//! Label : shown when the game quits
		std::string MsgEnd = "The end !";
		//! Label : pause
		std::string MsgPause = "\n\n\nPress enter to continue";
		//! Label : shown when someone catched someone "X catched.."
		std::string MsgCatch = " SUCCESSFULLY CATCHED HIS PREY!";
		//! Label : shown when someone escaped someone "X escaped.."
		std::string MsgEscape = " ESCAPED JUST IN TIME AND WON THIS ROUND!";
		//! Label : "hunts" in header "X hunts O [__ moves]"
		std::string MsgHeadHunts = "hunts";
		//! Label : "mvoes" in header "X hunts O [__ moves]"
		std::string MsgHeadMoves = "moves";
		//! Label : Is hunting message (x is hunting y)
		std::string MsgIsHunting = "IS HUNTING";
		//! Label : Round message (round x on y)
		std::string MsgRound = "ROUND";
		//! Label : "On" message (round x on y)
		std::string MsgOn = "ON";
		//! Label : "IS STUNNED" message (player x IS STUNNED)
		std::string MsgIsStunned = "IS STUNNED";
		//! Label : "Roles swapped" message
		std::string MsgRolesSwapped = "Roles swapped!";
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
		unsigned Round;
		//! Maximum number of rounds
		unsigned MaxRounds;
		//! Mouvements left
		unsigned MvLeft;
		//! Game lang
		int Lang;
		//! Play sound
		bool PlaySound;
		//! Localised strings
		SLangStrings LocaleStr;
		//! Contains last pressed keys
		std::vector <char> CharHistory;
		//! Counts total cycles done in a game loop
		unsigned CycleCount;
	};
}

#endif
