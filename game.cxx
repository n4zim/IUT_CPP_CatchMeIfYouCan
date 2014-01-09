/*!
 *
 * \file game.cxx
 * \author 
 * \date 09/01/14
 * \brief Fonctions du jeu
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
			//MoveToken (Mat, Input, PosP1, GameStatus.P1.Keys);
			MovedChar = MoveToken(Mat, Input, GameStatus.P1.Position, GameStatus.P1.Keys);
		} else if(Input == GameStatus.P2.Keys.Up || Input == GameStatus.P2.Keys.Down || Input == GameStatus.P2.Keys.Left || Input == GameStatus.P2.Keys.Right) {
			//MoveToken (Mat, Input, PosP2, GameStatus.P2.Keys);
			MovedChar = MoveToken(Mat, Input, GameStatus.P2.Position, GameStatus.P2.Keys);
		}

		return MovedChar;
	}

	bool GameLoop (CMatrix& Mat, SMapGenParams& MapGenParams, SGameStatus& GameStatus) {
		ShowMatrix (Mat, GameStatus.ColorSet);
		// cout << "input: " << endl;

		char Input = toupper (GetInput ());

		// Be able to quit the game
		if(Input == GameStatus.KeyExit)
			return false;

		char c = ProcessInput(Mat, Input, GameStatus);

		if(c == KTokenPlayer1 || c == KTokenPlayer2) 
			return false;

		return true;
	}

	void InitConfig (SGameStatus& GameStatus) {
		/*
		GameStatus.P1.Keys.Up    = 'Z';
		GameStatus.P1.Keys.Down  = 'S';
		GameStatus.P1.Keys.Left  = 'Q';
		GameStatus.P1.Keys.Right = 'D';
		GameStatus.P2.Keys.Up    = 'O';
		GameStatus.P2.Keys.Down  = 'L';
		GameStatus.P2.Keys.Left  = 'K';
		GameStatus.P2.Keys.Right = 'M';
		GameStatus.KeyPause   = 27;
		GameStatus.KeyExit    = 27;
		//*/
	}

	void StartGame () {
		CMatrix Mat;
		SGameStatus GameStatus = LoadGameConfig (".gameconfig"); // Load game config from file
		SMapGenParams MapGenParams = LoadMapGenConfig (".mapconfig"); // Load map config from file
		GameStatus.P1.Position = MapGenParams.PosPlayer1;
		GameStatus.P2.Position = MapGenParams.PosPlayer2;

		GenMap (Mat, MapGenParams, DIFFLVL_NORM);

		while (GameLoop (Mat, MapGenParams, GameStatus)) {
			
		}
		
		ShowMatrix (Mat, GameStatus.ColorSet);

	}  // ppal ()

}