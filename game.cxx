/*!
 *
 * \file game.cxx
 * \author 
 * \date 09/01/14
 * \brief Gameplay related functions
 * \version 1 
 */


#include <iostream>
#include <istream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <map>
#include <time.h> 
#include <stdlib.h>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "globals.hxx"
#include "unix.hxx" 
#include "file.hxx" 
#include "map.hxx" 
#include "audio.hxx" 
#include "bonus.hxx" 
#include "banana.hxx" 
#include "game.hxx" 

using namespace std;

namespace ChaseGame {
	char ProcessInput (CMatrix& Mat, const char Input, SGameStatus& GameStatus) {
		StoreCharHistory (Input, GameStatus);
		char MovedChar = KCancelled;

		if (Input == GameStatus.P1.Keys.Up || Input == GameStatus.P1.Keys.Down || Input == GameStatus.P1.Keys.Left || Input == GameStatus.P1.Keys.Right) {
			MovedChar = MoveToken (Mat, Input, GameStatus.P1.Position, GameStatus.P1.Keys);
			if (GameStatus.P1.IsChasing && MovedChar != KCancelled) 
				--GameStatus.MvLeft;
		} else if (Input == GameStatus.P2.Keys.Up || Input == GameStatus.P2.Keys.Down || Input == GameStatus.P2.Keys.Left || Input == GameStatus.P2.Keys.Right) {
			MovedChar = MoveToken (Mat, Input, GameStatus.P2.Position, GameStatus.P2.Keys);
			if (GameStatus.P2.IsChasing && MovedChar != KCancelled) 
				--GameStatus.MvLeft;
		} else if (Input == GameStatus.KeyExit) {
			return KExit;
		}

		return MovedChar;
	} // ProcessInput ()

	void StoreCharHistory (const char Input, SGameStatus& GameStatus) {
		if (GameStatus.CharHistory.size () > 1 && GameStatus.CharHistory[GameStatus.CharHistory.size () - 1] == Input)
			return; // Do not save duplicates

		if (GameStatus.CharHistory.size () < 6) {
			GameStatus.CharHistory.push_back (Input);
		} else {
			GameStatus.CharHistory.erase (GameStatus.CharHistory.begin ());	
			GameStatus.CharHistory.push_back (Input);
		}
	} // StoreCharHistory ()

	bool GameRoundLoop (CMatrix& Mat, SMapGenParams& MapGenParams, SGameStatus& GameStatus) {
		ShowMatrix (Mat, GameStatus.ColorSet);
		
		// Call the Bonus and Malus generator
		GenBonusMalus(Mat);

		char Input = toupper (GetInput ());

		char c = ProcessInput (Mat, Input, GameStatus);

		if (c == KTokenPlayer1 || c == KTokenPlayer2) {
			return false;
		} else if (c == KExit) {
			ClearScreen ();
			exit (0);
		}

		return true;
	} // GameRoundLoop ()

	bool GameLoop (SMapGenParams& MapGenParams, SGameStatus& GameStatus, map <string, sf::Music&>& Music) {
		CMatrix Mat;

		GenMap (Mat, MapGenParams, rand () % 4);
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
		if (GameStatus.PlaySound)
			SetGameState (Music, GMS_STARTING, true);

		Color (CLR_RESET);
		cout << "\n            [" << GameStatus.LocaleStr.MsgRound << " " << GameStatus.Round + 1 << " " << GameStatus.LocaleStr.MsgOn << " " << GameStatus.MaxRounds << "]";
		cout << "\n\n           {";
		Color (ColorH);
		cout << Hunter;
		Color (CLR_RESET);
		cout << " " << GameStatus.LocaleStr.MsgIsHunting << " ";
		Color (ColorP);
		cout << Prey;
		Color (CLR_RESET);
		cout << "}" << endl;

		Pause (true);
		if (GameStatus.PlaySound)
			SetGameState (Music, GMS_INGAME, true);

		GameStatus.MvLeft = (rand () % 25 + 10) * 10;
		GameStatus.CycleCount = 0;

		// The round starts here
		while (true) {
			ClearScreen ();
			Color (ColorH);
			cout << Hunter << " " << GameStatus.LocaleStr.MsgHeadHunts << " " << Prey << " ! [" << GameStatus.MvLeft << " " << GameStatus.LocaleStr.MsgHeadMoves << "]" << endl;

			if (GameStatus.MvLeft == 0) // if there is no more movements, we stop the game.
				break;

			if (!GameRoundLoop (Mat, MapGenParams, GameStatus)) // stop if someone catched someone
				break;

			// Detect the bonuses or maluses
			if (Mat[GameStatus.P1.Position.Y][GameStatus.P1.Position.X] == KBonus)
				Effect (Mat, GameStatus, 1, 0);
			if (Mat[GameStatus.P1.Position.Y][GameStatus.P1.Position.X] == KMalus)
				Effect (Mat, GameStatus, 0, 0);

			if (Mat[GameStatus.P2.Position.Y][GameStatus.P2.Position.X] == KBonus)
				Effect (Mat, GameStatus, 1, 1);
			if (Mat[GameStatus.P2.Position.Y][GameStatus.P2.Position.X] == KMalus)
				Effect (Mat, GameStatus, 0, 1);

			++GameStatus.CycleCount;

			// This is not an easter egg or anything
			if (GameStatus.CharHistory[0] == 66 && GameStatus.CharHistory[1] == 65 &&
				GameStatus.CharHistory[2] == 78 && GameStatus.CharHistory[3] == 65 &&
				GameStatus.CharHistory[4] == 78 && GameStatus.CharHistory[5] == 65) {
				SetGameState (Music, GMS_STOP, true);
				SuperBanana ();
			}
		}

		// Round end

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

		if (HunterWon) {
			Color (ColorH);
			cout << Hunter << GameStatus.LocaleStr.MsgCatch << endl;
		} else {
			Color (ColorP);
			cout << Prey << GameStatus.LocaleStr.MsgEscape << endl;
		}

		ShowMatrix (Mat, GameStatus.ColorSet);
		if (GameStatus.PlaySound)
			SetGameState (Music, GMS_STARTING, true);

		Pause (true);
		if (GameStatus.PlaySound)
			SetGameState (Music, GMS_TITLE, true);

		++GameStatus.Round;

		ClearScreen ();

		Color (CLR_GREEN);
		cout << "\n";
		cout << "  .oPYo. .oPYo. .oPYo.  .oPYo. .oPYo.  .oPYo. .oPYo.      .oo  .oPYo. ooo.   \n";
		cout << "  8      8    8 8    8  8   `8 8.      8   `8 8    8     .P 8  8   `8 8  `8. \n";
		cout << "  `Yooo. 8      8    8 o8YooP' `boo   o8YooP' 8    8    .P  8 o8YooP' 8   `8 \n";
		cout << "      `8 8      8    8  8   `b .P      8   `b 8    8   oPooo8  8   `b 8    8 \n";
		cout << "       8 8    8 8    8  8    8 8       8    8 8    8  .P    8  8    8 8   .P \n";
		cout << "  `YooP' `YooP' `YooP'  8    8 `YooP'  8oooP' `YooP' .P     8  8    8 8ooo'  \n";
		Color (CLR_RESET);
		cout << "  :.....::.....::.....::..:::..:.....::......::.....:..:::::..:..:::.......::\n";
		cout << "  :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << "  ::::::::::::::::::::::::::- ";
		Color (GameStatus.ColorSet.ColorP1);
		cout << "PLAYER " << KTokenPlayer1 << " > " << setw(3) << GameStatus.P1.Score << " pts";
		Color (CLR_RESET);
		cout << " -:::::::::::::::::::::::::::\n";
		cout << "  ::::::::::::::::::::::::::- ";
		Color (GameStatus.ColorSet.ColorP2);
		cout << "PLAYER " << KTokenPlayer2 << " > " << setw(3) << GameStatus.P2.Score << " pts";
		Color (CLR_RESET);
		cout << " -:::::::::::::::::::::::::::\n";
		cout << "  :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << "  ...........................................................................\n";
		
		Pause (true);

		return GameStatus.Round < GameStatus.MaxRounds;
	}

	void StartGame () {
		SGameStatus GameStatus = LoadGameConfig (".gameconfig"); // Load game config from file
		SMapGenParams MapGenParams = LoadMapGenConfig (".mapconfig"); // Load map config from file
		// Init sound-related variables
		sf::Music Track1A, Track1B, Track1C, Track2;
		InitSongs (Track1A, Track1B, Track1C, Track2);

		GameStatus.P1.IsChasing = true;
		GameStatus.P2.IsChasing = false;
		GameStatus.P1.Score = 0;
		GameStatus.P2.Score = 0;

		GameStatus.Round = 0;
		//GameStatus.MaxRounds = 4;

		// SOUND INITIALISATION

		// MUSIC LOADING
		map <string, sf::Music&> Tracks = {{ "A1", Track1A }, { "B1", Track1B }, { "C1", Track1C }, { "2", Track2 }};

		if (GameStatus.PlaySound) {
			SetGameState (Tracks, GMS_TITLE, false);
		} else {
			SetGameState (Tracks, GMS_STOP, false);
		}

		// Title screen
		ClearScreen ();

		cout << "\n";
		cout << "  .oPYo.  o    o      .oo .oPYo. .oPYo.   .oPYo.      .oo o     o .oPYo. \n";
		cout << "  7    8  8    8     .P 8 8      8.       8    8     .P 8 8b   d8 8.     \n";
		cout << "  8      o8oooo8    .P  8 `Yooo. `boo     8         .P  8 8`b d'8 `boo   \n";
		cout << "  8       8    8   oPooo8     `8 .P       8   oo   oPooo8 8 `o' 8 .P     \n";
		cout << "  7    8  8    8  .P    8      8 8        8    8  .P    8 8     8 8      \n";
		cout << "  `YooP'  8    8 .P     8 `YooP' `YooP'   `YooP8 .P     8 8     8 `YooP' \n";
		cout << "  :.....::..:::....:::::..:.....::.....::::....8 ..:::::....::::..:.....:\n";
		cout << "  :::::::::::::::::::::::::::::::::::::::::::::8 ::::::::::::::::::::::::\n";
		cout << "  :::::::::::::::::::::::::::::::::::::::::::::..::::::::::::::::::::::::\n";
		cout << "  :::::::::::::- " << GameStatus.LocaleStr.TitlePlayGameLabel    << " -::::::::::::::\n";
		cout << "  :::::::::::::- " << GameStatus.LocaleStr.TitleGameOptionsLabel << " -::::::::::::::\n";
		cout << "  :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << "  .......................................................................\n" << endl;
		
		Pause (false);

		// Display Key configuration
		ClearScreen ();

		cout << "\n";
		cout << "   o   o .oPYo. o   o   .oPYo. .oPYo. o    o  ooooo o .oPYo. \n";
		cout << "   8  .P 8.     `b d'   8    8 8    8 8b   8  8     8 8    8 \n";
		cout << "  o8ob'  `boo    `b'    8      8    8 8`b  8 o8oo   8 8      \n";
		cout << "   8  `b .P       8     8      8    8 8 `b 8  8     8 8   oo \n";
		cout << "   8   8 8        8     8    8 8    8 8  `b8  8     8 8    8 \n";
		cout << "   8   8 `YooP'   8     `YooP' `YooP' 8   `8  8     8 `YooP8 \n";
		cout << "  :..::..:.....:::..:::::.....::.....:..:::..:..::::..:....8 \n";
		cout << "  :::::::::::::::::::::::::::::::::::::::::::::::::::::::::8 \n";
		cout << "  :::::." << GameStatus.LocaleStr.TitlePlayer1  << ".:::.." << GameStatus.LocaleStr.TitleRules << "..:::." << GameStatus.LocaleStr.TitlePlayer2  << ".::::: \n";
		cout << "  :::::. " << setw(5) << GameStatus.LocaleStr.DirUp    << " > " << char (GameStatus.P1.Keys.Up   ) << " .:::. " << GameStatus.LocaleStr.TitleMGRL1 << " .:::. " << setw(5) << GameStatus.LocaleStr.DirUp    << " > " << char (GameStatus.P2.Keys.Up   ) << " .::::: \n";
		cout << "  :::::. " << setw(5) << GameStatus.LocaleStr.DirDown  << " > " << char (GameStatus.P1.Keys.Down ) << " .:::. " << GameStatus.LocaleStr.TitleMGRL2 << " .:::. " << setw(5) << GameStatus.LocaleStr.DirDown  << " > " << char (GameStatus.P2.Keys.Down ) << " .::::: \n";
		cout << "  :::::. " << setw(5) << GameStatus.LocaleStr.DirLeft  << " > " << char (GameStatus.P1.Keys.Left ) << " .:::. " << GameStatus.LocaleStr.TitleMGRL3 << " .:::. " << setw(5) << GameStatus.LocaleStr.DirLeft  << " > " << char (GameStatus.P2.Keys.Left ) << " .::::: \n";
		cout << "  :::::. " << setw(5) << GameStatus.LocaleStr.DirRight << " > " << char (GameStatus.P1.Keys.Right) << " .:::................:::. " << setw(5) << GameStatus.LocaleStr.DirRight << " > " << char (GameStatus.P2.Keys.Right) << " .::::: \n";
		cout << "  :::::::::::::::::::::::::::::::::::::::::::::::::::::::::: \n";
		cout << "  :::::::::::::::::::::::::::::::::::::::::::::::::::::::::: \n";
		cout << "  .......................................................... \n" << endl;

		cout << GameStatus.LocaleStr.MsgPause;
		Pause (false);

		// MAIN LIFE LOOP
		while (GameLoop (MapGenParams, GameStatus, Tracks)) {
			if (GameStatus.P1.IsChasing) {
				GameStatus.P1.IsChasing = false;
				GameStatus.P2.IsChasing = true;
			} else {
				GameStatus.P1.IsChasing = true;
				GameStatus.P2.IsChasing = false;
			}
		}

		if (GameStatus.P1.Score == GameStatus.P2.Score) { // TIE
				// A random player is hunting the other
				GameStatus.P1.IsChasing = (rand() % 2 == 1);
				GameStatus.P2.IsChasing = !GameStatus.P1.IsChasing;

				cout << GameStatus.LocaleStr.MsgTie << endl;

				cout << GameStatus.LocaleStr.MsgPause;
				Pause (false);
				++GameStatus.MaxRounds;
				GameLoop (MapGenParams, GameStatus, Tracks);
		}

		cout << GameStatus.LocaleStr.MsgEnd << endl;

	}  // ppal ()

}