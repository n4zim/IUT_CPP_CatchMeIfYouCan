/*!
 *
 * \file file.cxx
 * \author 
 * \date 08/01/14
 * \brief File related functions
 * \version 1
 *
 * Contains functions that loads or save config files
 * 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "globals.hxx"
#include "file.hxx"

using namespace std;

namespace ChaseGame {

	SMapGenParams LoadMapGenConfig (const string & FileName) {
		SMapGenParams Params; 

		// Defining the default map
		Params.MapHeight = 10;
		Params.MapWidth = 30;

		Params.PosPlayer1.X = 0;
		Params.PosPlayer1.Y = 9;
		Params.PosPlayer2.X = 29;
		Params.PosPlayer2.Y = 0;

		// open config file
		ifstream file (FileName);

		// If the config file doesn't exists, we create it and we return the default map parameters
		if (!file) {
			SaveMapConfig (FileName, Params); // Saves the config file for later use
			return Params; // Returns the default config
		}
		
		// Config file reading (format : "string: int")
		for (;file;) {
			string VarId;
			int Value = 0;
			file >> VarId >> Value;

			if (VarId == "MapHeight")
				Params.MapHeight = Value;
			else if (VarId == "MapWidth")
				Params.MapWidth = Value;
			else if (VarId == "PosP1.X")
				Params.PosPlayer1.X = Value;
			else if (VarId == "PosP1.Y")
				Params.PosPlayer1.Y = Value;
			else if (VarId == "PosP2.X")
				Params.PosPlayer2.X = Value;
			else if (VarId == "PosP1.Y")
				Params.PosPlayer2.Y = Value;
		}  

		// Returning the parameters
		return Params;
	}


	bool SaveMapConfig (const string& FileName, SMapGenParams& Params) {
		ofstream file (FileName);

		if (!file)
			return false; // File can't be written

		file << "MapHeight " << Params.MapHeight << endl;
		file << "MapWidth " << Params.MapWidth << endl;
		file << "PosP1.X " << Params.PosPlayer1.X << endl;
		file << "PosP1.Y " << Params.PosPlayer1.Y << endl;
		file << "PosP2.X " << Params.PosPlayer2.X << endl;
		file << "PosP2.Y " << Params.PosPlayer2.Y << endl;

		return true;
	}


	SGameStatus LoadGameConfig (const std::string & FileName) {
		SGameStatus Config; 
		
		Config.P1.Keys.Up    = 'Z';
		Config.P1.Keys.Down  = 'S';
		Config.P1.Keys.Left  = 'Q';
		Config.P1.Keys.Right = 'D';

		Config.P2.Keys.Up    = 'O';
		Config.P2.Keys.Down  = 'L';
		Config.P2.Keys.Left  = 'K';
		Config.P2.Keys.Right = 'M';

		Config.KeyPause = 27;
		Config.KeyExit  = 27;

		Config.MaxRounds = 4;
		Config.PlaySound = true;
		Config.Lang      = LANG_EN;

		Config.ColorSet.ColorP1 = CLR_RED;
		Config.ColorSet.ColorP2 = CLR_BLUE;
		Config.ColorSet.ColorObstacle = CLR_CYAN;
		Config.ColorSet.ColorWall = CLR_CYAN;
		Config.ColorSet.ColorBonus = CLR_GREEN;
		Config.ColorSet.ColorMalus = CLR_RED;

		// open config file
		ifstream file (FileName);

		// If the config file doesn't exists, we create it and we save+return the default config
		if (!file) {
			SaveGameConfig (FileName, Config); // Saves the config file for later use
			return Config; // Returns the default config
		}
		
		// Config file reading (format : "string: int")
		for (;file;) {
			string VarId;
			int Value = 0;
			file >> VarId >> Value;

			// P1 keys
			if (VarId == "KeyP1Up")
				Config.P1.Keys.Up = char(Value);
			else if (VarId == "KeyP1Left")
				Config.P1.Keys.Left = char(Value);
			else if (VarId == "KeyP1Right")
				Config.P1.Keys.Right = char(Value);
			else if (VarId == "KeyP1Down")
				Config.P1.Keys.Down = char(Value);

			// P2 keys
			else if (VarId == "KeyP2Up")
				Config.P2.Keys.Up = char(Value);
			else if (VarId == "KeyP2Left")
				Config.P2.Keys.Left = char(Value);
			else if (VarId == "KeyP2Right")
				Config.P2.Keys.Right = char(Value);
			else if (VarId == "KeyP2Down")
				Config.P2.Keys.Down = char(Value);

			// Color config
			else if (VarId == "ColorP1")
				Config.ColorSet.ColorP1 = Value;
			else if (VarId == "ColorP2")
				Config.ColorSet.ColorP2 = Value;
			else if (VarId == "ColorObstacle")
				Config.ColorSet.ColorObstacle = Value;
			else if (VarId == "ColorWall")
				Config.ColorSet.ColorWall = Value;
			else if (VarId == "ColorBonus")
				Config.ColorSet.ColorBonus = Value;
			else if (VarId == "ColorMalus")
				Config.ColorSet.ColorMalus = Value;

			// Other config
			else if (VarId == "Lang")
				Config.Lang = Value;
			else if (VarId == "MaxRounds")
				Config.MaxRounds = Value;
			else if (VarId == "PlaySound")
				Config.PlaySound = (Value > 0) ? true : false;
		}  

		return Config;
	}


	bool SaveGameConfig (const string& FileName, SGameStatus& Config) {
		ofstream file (FileName);

		if (!file)
			return false; // File can't be written

		file << "KeyP1Up " << Config.P1.Keys.Up << endl;
		file << "KeyP1Down " << Config.P1.Keys.Down << endl;
		file << "KeyP1Left " << Config.P1.Keys.Left << endl;
		file << "KeyP1Right " << Config.P1.Keys.Right << endl;

		file << "KeyP2Up " << Config.P2.Keys.Up << endl;
		file << "KeyP2Down " << Config.P2.Keys.Down << endl;
		file << "KeyP2Left " << Config.P2.Keys.Left << endl;
		file << "KeyP2Right " << Config.P2.Keys.Right << endl;

		file << "ColorP1 " << Config.ColorSet.ColorP1 << endl;
		file << "ColorP2 " << Config.ColorSet.ColorP2 << endl;
		file << "ColorObstacle " << Config.ColorSet.ColorObstacle << endl;
		file << "ColorWall " << Config.ColorSet.ColorWall << endl;
		file << "ColorBonus " << Config.ColorSet.ColorBonus << endl;
		file << "ColorMalus " << Config.ColorSet.ColorMalus << endl;

		file << "Lang " << Config.Lang << endl;
		file << "MaxRounds " << Config.MaxRounds << endl;
		file << "PlaySound " << Config.PlaySound << endl;

		return true;
	}
}