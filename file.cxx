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

			if (VarId == "NbLine:")
				Params.MapHeight = Value;
			else if (VarId == "NbCol:")
				Params.MapWidth = Value;
			else if (VarId == "PosP1.X:")
				Params.PosPlayer1.X = Value;
			else if (VarId == "PosP1.Y:")
				Params.PosPlayer1.Y = Value;
			else if (VarId == "PosP2.X:")
				Params.PosPlayer2.X = Value;
			else if (VarId == "PosP1.Y:")
				Params.PosPlayer2.Y = Value;
		}  

		// Returning the parameters
		return Params;
	}


	bool SaveMapConfig (const string& FileName, SMapGenParams Params) {
		ofstream file (FileName);

		if (!file)
			return false; // File can't be written

		file << "MapHeight: " << Params.MapHeight << endl;
		file << "MapWidth: " << Params.MapWidth << endl;
		file << "PosP1.X: " << Params.PosPlayer1.X << endl;
		file << "PosP1.Y: " << Params.PosPlayer1.Y << endl;
		file << "PosP2.X: " << Params.PosPlayer2.X << endl;
		file << "PosP2.Y: " << Params.PosPlayer2.Y << endl;

		return true;
	}


	SGameStatus LoadGameConfig (const std::string & FileName) {
		SGameStatus Params; 
		
		return Params;
	}

}