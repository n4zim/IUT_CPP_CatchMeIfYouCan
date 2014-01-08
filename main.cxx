/*!
 *
 * \file main.cxx
 * \author Josua Gonzalez
 * \date 17/12/13
 * \brief Fichier du tp qui fait un jeu de catch me if you can
 * \version 1
 *
 * Jeu de "Catch me if you can", projet c++
 * 
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



/*! \namespace ChaseGame
 * Project namespace for the game
 */
namespace ChaseGame {

	/*!
	 * \brief Processes user input
	 * \param Mat Game Matrix
	 * \param Input input given
	 * \param PosP1 Player 1 position
	 * \param PosP2 Player 2 position
	 * \param Config Game configuration
	 * \return Char
	 */
	char ProcessInput(CMatrix& Mat, const char Input, SGameStatus& Config) {
		char MovedChar = KEmpty;
		if(Input == Config.P1.Keys.Up || Input == Config.P1.Keys.Down || Input == Config.P1.Keys.Left || Input == Config.P1.Keys.Right) {
			//MoveToken (Mat, Input, PosP1, Config.P1.Keys);
			MovedChar = MoveToken(Mat, Input, Config.P1.Position, Config.P1.Keys);
		} else if(Input == Config.P2.Keys.Up || Input == Config.P2.Keys.Down || Input == Config.P2.Keys.Left || Input == Config.P2.Keys.Right) {
			//MoveToken (Mat, Input, PosP2, Config.P2.Keys);
			MovedChar = MoveToken(Mat, Input, Config.P2.Position, Config.P2.Keys);
		}

		return MovedChar;
	}

	/*!
	 * \brief This is the game loop
	 * \param Mat Game Matrix
	 * \param MapGenParams Map generator parameters
	 * \param PosP1 Player 1 position
	 * \param PosP2 Player 2 position
	 * \param Config Game configuration
	 * \return true If game is running
	 * \return false If game is ended
	 */
	bool GameLoop (CMatrix& Mat, SMapGenParams& MapGenParams, SGameStatus& Config) {
		ShowMatrix(Mat);
		cout << "input : " << endl;

		char Input = toupper(GetInput());

		// Be able to quit the game
		if(Input == Config.KeyExit)
			return false;

		char c = ProcessInput(Mat, Input, Config);

		if(c == KTokenPlayer1 || c == KTokenPlayer2) 
			return false;

		return true;
	}

	/*!
	 * \brief This function inits the config
	 * \param  Config Game config struct
	 */
	void InitConfig (SGameStatus& Config) {
		Config.P1.Keys.Up    = 'Z';
		Config.P1.Keys.Down  = 'S';
		Config.P1.Keys.Left  = 'Q';
		Config.P1.Keys.Right = 'D';
		Config.P2.Keys.Up    = 'O';
		Config.P2.Keys.Down  = 'L';
		Config.P2.Keys.Left  = 'K';
		Config.P2.Keys.Right = 'M';
		/*Config.P2.Keys.Up    = OSKCODE_ARRUP;
		Config.P2.Keys.Down  = OSKCODE_ARRDOWN;
		Config.P2.Keys.Left  = OSKCODE_ARRLEFT;
		Config.P2.Keys.Right = OSKCODE_ARRRIGHT;*/
		Config.KeyPause   = 27;
		Config.KeyExit    = 27;
	}

	/*!
	 * \brief This function starts the game
	 */
	void StartGame () {
		CMatrix Mat;
		SGameStatus Config;
		InitConfig(Config);

		SMapGenParams MapGenParams = LoadMapGenConfig (".mapconfig"); // Load map config from file
		Config.P1.Position = MapGenParams.PosPlayer1;
		Config.P2.Position = MapGenParams.PosPlayer2;

		GenMap (Mat, MapGenParams);

		while (GameLoop(Mat, MapGenParams, Config)) {
			
		}
		
		ShowMatrix(Mat);

	}  // ppal ()

}

/*!
 * \brief Program main, the program does not accept arguments.
 * \return 0
 */
int main () {
  	srand (time (NULL));
	ChaseGame::StartGame ();
	return 0;
}