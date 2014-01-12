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
	char ProcessInput (CMatrix& Mat, const char Input, SGameStatus& GameStatus, int& MovedPlayer) {
		StoreCharHistory (Input, GameStatus);
		char MovedChar = KCancelled;

		if (Input == GameStatus.P1.Keys.Up || Input == GameStatus.P1.Keys.Down || Input == GameStatus.P1.Keys.Left || Input == GameStatus.P1.Keys.Right) {
			MovedChar = MoveToken (Mat, Input, GameStatus.P1, GameStatus.P1.Keys);
			if (GameStatus.P1.IsChasing && MovedChar != KCancelled) 
				--GameStatus.MvLeft;
			MovedPlayer = 1;
		} else if (Input == GameStatus.P2.Keys.Up || Input == GameStatus.P2.Keys.Down || Input == GameStatus.P2.Keys.Left || Input == GameStatus.P2.Keys.Right) {
			MovedChar = MoveToken (Mat, Input, GameStatus.P2, GameStatus.P2.Keys);
			if (GameStatus.P2.IsChasing && MovedChar != KCancelled) 
				--GameStatus.MvLeft;
			MovedPlayer = 2;
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
		int MovedPlayer = 0;
		ShowMatrix (Mat, GameStatus.ColorSet);
		
		// Call the Bonus and Malus generator
		GenBonusMalus(Mat);

		char Input = toupper (GetInput ());

		char c = ProcessInput (Mat, Input, GameStatus, MovedPlayer);

		if (c == KTokenPlayer1 || c == KTokenPlayer2) {
			return false;
		} else if (c == KBonus) {
			if (MovedPlayer == 1)
				Effect (GameStatus, 1, 0);
			else
				Effect (GameStatus, 1, 1);

		} else if (c == KMalus) {
			if (MovedPlayer == 0)
				Effect (GameStatus, 0, 0);
			else
				Effect (GameStatus, 0, 1);

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

		cout << GameStatus.LocaleStr.MsgPause;
		Pause (false);

		if (GameStatus.PlaySound)
			SetGameState (Music, GMS_INGAME, true);

		GameStatus.MvLeft = (rand () % 25 + 10) * 10;
		GameStatus.CycleCount = 0;

		// The round starts here
		while (true) {
			ClearScreen ();

			Color (ColorH);
			cout << Hunter << " " << GameStatus.LocaleStr.MsgHeadHunts << " " << Prey << " ! [" << GameStatus.MvLeft << " " << GameStatus.LocaleStr.MsgHeadMoves << "] ";
			
			Color (CLR_RESET);
			if(GameStatus.P1.IsStunned) 
				cout << "[" << KTokenPlayer1 << " IS STUNNED]";
			else if(GameStatus.P2.IsStunned) 
				cout << "[" << KTokenPlayer2 << " IS STUNNED]";
			cout << endl;


			if (GameStatus.MvLeft == 0) // if there is no more movements, we stop the game.
				break;

			if (!GameRoundLoop (Mat, MapGenParams, GameStatus)) // stop if someone catched someone
				break;

			++GameStatus.CycleCount;

			// This is not an easter egg or anything
			if (GameStatus.CharHistory[0] == 66 && GameStatus.CharHistory[1] == 65 &&
				GameStatus.CharHistory[2] == 78 && GameStatus.CharHistory[3] == 65 &&
				GameStatus.CharHistory[4] == 78 && GameStatus.CharHistory[5] == 65) {
				SetGameState (Music, GMS_STOP, true);
				SuperBanana ();
			}

			// recalculate roles because they can change during the game
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

			CheckStun(GameStatus.P1);
			CheckStun(GameStatus.P2);
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

		cout << GameStatus.LocaleStr.MsgPause;
		Pause (false);
		
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
		
		cout << GameStatus.LocaleStr.MsgPause;
		Pause (false);

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

		// LANGUAGE MENU
		ClearScreen ();

		cout << endl;
        string Reply;

        bool OutMenuLang = false;
        while(!OutMenuLang) {

	        cout << "\n       Langage         /       Language        /       Lengaje\n\n\n";
	        cout << "       1 . Français "  << endl;
	        cout << "       2 . English  "  << endl;
	        cout << "       3 . Enpanol\n";

	        if(Reply == "")
	        	cout << "\n\n";
	        else
	        	cout << "\nErreur de l'entée   /   Input error   /   Error de valor\n";

	        cout << "\nChoisissez votre langue / Choose your language / Elige tu lengua : ";

        	cin >> Reply;

	        Reply = Reply[0];
	        unsigned Result;
	        {
	            istringstream is(Reply);
	            is >> Result;
	        } // convert Reply[0] (string) to unsigned 

            switch (Result) {
                case 1:
                GameStatus.Lang = LANG_FR;
                OutMenuLang = true;  
                break ;
                                
                case 2:
                GameStatus.Lang = LANG_EN;
                OutMenuLang = true;
                break;
                                               
                case 3:
                GameStatus.Lang = LANG_ES;
                OutMenuLang = true;
                break;  

                default:
                Reply == "";
                ClearScreen ();
                cout << endl;
        		break;
            }
        }

        // Language definition
		if (GameStatus.Lang == LANG_FR) {
			GameStatus.LocaleStr.TitlePlayGameLabel    = "TAPE 'PLAY' POUR JOUER OU ...      ";
			GameStatus.LocaleStr.TitleGameOptionsLabel = "TAPE 'OPTIONS' POUR CONFIGURER !   ";
			GameStatus.LocaleStr.DirUp = "HAUT";
			GameStatus.LocaleStr.DirLeft = "BAS";
			GameStatus.LocaleStr.DirDown = "GAUCHE";
			GameStatus.LocaleStr.DirRight = "DROITE";
			GameStatus.LocaleStr.TitleMGRL1 = " JOUEUR 1 ";
			GameStatus.LocaleStr.TitleMGRL2 = "DOIT CHOPER";
			GameStatus.LocaleStr.TitleMGRL3 = "  L'AUTRE ";
			GameStatus.LocaleStr.TitlePlayer1 = "..JOUEUR1..";
			GameStatus.LocaleStr.TitlePlayer2 = "..JOUEUR2..";
			GameStatus.LocaleStr.TitleRules = "....REGLE...";
			GameStatus.LocaleStr.MsgTie = "\n  EGALITE !\n Maintenant, commencez une nouvelle manche pour connaîte le grand Gagnant ...";
			GameStatus.LocaleStr.MsgEnd = "FIN !";
			GameStatus.LocaleStr.MsgPause = "\n\n\nAppuyez sur entrer pour continuer";
			GameStatus.LocaleStr.MsgCatch = " A ATTRAPE SA PROIE!";
			GameStatus.LocaleStr.MsgEscape = " A reussi à s'échaper dans les temps!";
			GameStatus.LocaleStr.MsgHeadHunts = "chasse";
			GameStatus.LocaleStr.MsgHeadMoves = "mouvements";
			GameStatus.LocaleStr.MsgIsHunting = "chasse";
			GameStatus.LocaleStr.MsgRound = "MANCHE";
			GameStatus.LocaleStr.MsgOn = "SUR";
		} else if (GameStatus.Lang == LANG_ES) {
			GameStatus.LocaleStr.TitlePlayGameLabel    = "ENTRAR 'PLAY' PARA JUGAR O  ...      ";
			GameStatus.LocaleStr.TitleGameOptionsLabel = "ENTRAR 'OPTIONS' PARA CONFIGURAR !   ";
			GameStatus.LocaleStr.DirUp = "ARRIBA";
			GameStatus.LocaleStr.DirLeft = "BASTA";
			GameStatus.LocaleStr.DirDown = "GAUCHA";
			GameStatus.LocaleStr.DirRight = "DROITA";
			GameStatus.LocaleStr.TitleMGRL1 = " JUU 1 ";
			GameStatus.LocaleStr.TitleMGRL2 = "DEBE COGER";
			GameStatus.LocaleStr.TitleMGRL3 = "  OTRO ";
			GameStatus.LocaleStr.TitlePlayer1 = "..JUGADOR1..";
			GameStatus.LocaleStr.TitlePlayer2 = "..JUGADOR2..";
			GameStatus.LocaleStr.TitleRules = "....REGLAS...";
			GameStatus.LocaleStr.MsgTie = "\n  EGUALDAD !\n Empezamos una nueva manga para determinar quien es el ganador real.";
			GameStatus.LocaleStr.MsgEnd = "FIN !";
			GameStatus.LocaleStr.MsgPause = "\n\n\nENTRAR PARA CONTINUAR";
			GameStatus.LocaleStr.MsgCatch = " HA CAPTURADOS SU PRESA!";
			GameStatus.LocaleStr.MsgEscape = " Escapo a tiempó !";
			GameStatus.LocaleStr.MsgHeadHunts = "caza";
			GameStatus.LocaleStr.MsgHeadMoves = "movimientos";
			GameStatus.LocaleStr.MsgIsHunting = "esta cazando";
			GameStatus.LocaleStr.MsgRound = "MANGA";
			GameStatus.LocaleStr.MsgOn = "DE";
		}

		// Title screen
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