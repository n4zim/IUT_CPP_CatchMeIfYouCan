/*!
 *
 * \file game.cxx
 * \author 
 * \date 09/01/14
 * \brief Gameplay related functions
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

using namespace std;

namespace ChaseGame {

	char ProcessInput (CMatrix& Mat, const char Input, SGameStatus& GameStatus) {
		char MovedChar = KCancelled;
		if(Input == GameStatus.P1.Keys.Up || Input == GameStatus.P1.Keys.Down || Input == GameStatus.P1.Keys.Left || Input == GameStatus.P1.Keys.Right) {
			MovedChar = MoveToken(Mat, Input, GameStatus.P1.Position, GameStatus.P1.Keys);
			if(GameStatus.P1.IsChasing) 
				--GameStatus.MvLeft;
		} else if(Input == GameStatus.P2.Keys.Up || Input == GameStatus.P2.Keys.Down || Input == GameStatus.P2.Keys.Left || Input == GameStatus.P2.Keys.Right) {
			MovedChar = MoveToken(Mat, Input, GameStatus.P2.Position, GameStatus.P2.Keys);
			if(GameStatus.P2.IsChasing) 
				--GameStatus.MvLeft;
		}

		return MovedChar;
	} // ProcessInput ()

	bool GameRoundLoop (CMatrix& Mat, SMapGenParams& MapGenParams, SGameStatus& GameStatus) {
		ShowMatrix (Mat, GameStatus.ColorSet);
		// cout << "input: " << endl;

		char Input = toupper (GetInput ());

		/*
		// Be able to quit the game
		if(Input == GameStatus.KeyExit)
			return false; // */

		char c = ProcessInput(Mat, Input, GameStatus);

		if(c == KTokenPlayer1 || c == KTokenPlayer2) {
			return false;
		}

		return true;
	} // GameRoundLoop ()

	void Pause () {
		Color(CLR_RESET);

		cout << "\n\n\nPress enter to continue";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(!cin) {
            cin.clear();
        }
	} // Pause ()

	bool GameLoop (SMapGenParams& MapGenParams, SGameStatus& GameStatus) {
		CMatrix Mat;

		GenMap (Mat, MapGenParams, DIFFLVL_NORM);
		GameStatus.P1.Position = MapGenParams.PosPlayer1;
		GameStatus.P2.Position = MapGenParams.PosPlayer2; 

 		// Display "round X" stuff
		char Hunter, Prey;
 		int ColorH, ColorP;
		if (GameStatus.P1.IsChasing) {
			Hunter = KTokenPlayer1;
			Prey = KTokenPlayer2;
			ColorH = GameStatus.ColorSet.ColorP1;
			ColorP = GameStatus.ColorSet.ColorP2;
		} else {
			Hunter = KTokenPlayer2;
			Prey = KTokenPlayer1;
			ColorH = GameStatus.ColorSet.ColorP2;
			ColorP = GameStatus.ColorSet.ColorP1;
		}

		ClearScreen ();
		Color (CLR_RESET);
		cout << "\n               [ROUND " << GameStatus.Round + 1 << "]";
		cout << "\n\n           {";
		Color (ColorH);
		cout << Hunter;
		Color (CLR_RESET);
		cout << " IS HUNTING ";
		Color (ColorP);
		cout << Prey;
		Color (CLR_RESET);
		cout << "}" << endl;

		Pause ();

		GameStatus.MvLeft = (rand() % 7 + 5) * 10;

		// The round starts here
		while (true) {
			ClearScreen ();
			Color(ColorH);
			cout << Hunter << " moves left : " << GameStatus.MvLeft << endl;

			if (GameStatus.MvLeft == 0) // if there is no more movements, we stop the game.
				break;

			if (!GameRoundLoop (Mat, MapGenParams, GameStatus)) // stop if someone catched someone
				break;
		}

		ClearScreen ();

		bool HunterWon = false;
		
		if (GameStatus.MvLeft != 0) {
			HunterWon = true;
		}
		
		if (GameStatus.P1.IsChasing) {
			if (HunterWon) {
				++GameStatus.P1.Score;
			} else {
				++GameStatus.P2.Score;
			}
		} else {
			if (HunterWon) {
				++GameStatus.P2.Score;
			} else {
				++GameStatus.P1.Score;
			}
		}

		if(HunterWon) {
			Color(ColorH);
			cout << Hunter << " SUCCESSFULLY CATCHED HIS PREY!" << endl;
		} else {
			Color(ColorP);
			cout << Prey << " ESCAPED JUST IN TIME AND WON THIS ROUND!" << endl;
		}

		ShowMatrix (Mat, GameStatus.ColorSet);

		Pause ();

		++GameStatus.Round;

		ClearScreen ();
		cout << "\n >>> Scores >>>" << endl; 
		Color(GameStatus.ColorSet.ColorP1);
		cout << "  > " << KTokenPlayer1 << " : " << GameStatus.P1.Score << endl;
		Color(GameStatus.ColorSet.ColorP2);
		cout << "  > " << KTokenPlayer2 << " : " << GameStatus.P2.Score << endl;
		
		Pause ();

		return GameStatus.Round < GameStatus.MaxRounds;
	}

	void StartGame () {
		SGameStatus GameStatus = LoadGameConfig (".gameconfig"); // Load game config from file
		SMapGenParams MapGenParams = LoadMapGenConfig (".mapconfig"); // Load map config from file

		GameStatus.P1.IsChasing = true;
		GameStatus.P2.IsChasing = false;
		GameStatus.P1.Score = 0;
		GameStatus.P2.Score = 0;

		GameStatus.Round = 0;
		GameStatus.MaxRounds = 5;

		// Title screen
		ClearScreen ();
		cout << "Écran titre avec menu" << endl;
		GetInput ();

		// MAIN LIFE LOOP
		while(GameLoop (MapGenParams, GameStatus)) {
			if(GameStatus.P1.IsChasing) {
				GameStatus.P1.IsChasing = false;
				GameStatus.P2.IsChasing = true;
			} else {
				GameStatus.P1.IsChasing = true;
				GameStatus.P2.IsChasing = false;
			}
		}

		cout << "Game end" << endl;

	}  // ppal ()

}