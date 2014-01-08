/*!
 *
 * \file map.cxx
 * \author 
 * \date 08/01/14
 * \brief Map related function
 * \version 1
 *
 * Contains functions that generate the map, displays it, move tokens and other related functions.
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "globals.hxx"
#include "windows.hxx" 
#include "unix.hxx"

using namespace std;

namespace ChaseGame {

	void GenMap (CMatrix & Mat, SMapGenParams Params) {
		for (unsigned i = 0; i < Params.MapHeight; ++i) {
			CVLine Line;
			for (unsigned j = 0; j < Params.MapWidth; ++j) {
				Line.push_back (KEmpty);
			}
			Mat.push_back (Line);
		}

		Mat[Params.PosPlayer1.Y][Params.PosPlayer1.X] = KTokenPlayer1;
		Mat[Params.PosPlayer2.Y][Params.PosPlayer2.X] = KTokenPlayer2;
	} // GenMap ()


	char MoveToken (CMatrix & Mat, char Move, SPlayerPos & Pos, const SPlayerKeys& KeyCodes)	{
		bool ValidMove = true;
		char replacedChar = KEmpty;
		SPlayerPos NewPos = Pos;

	 	if (Move == KeyCodes.Up && NewPos.Y > 0) {
		  	NewPos.Y -= 1; 
		} else if (Move == KeyCodes.Left && NewPos.X > 0) {
		  	NewPos.X -= 1; 
		} else if (Move == KeyCodes.Right && NewPos.X < Mat[Pos.Y].size() - 1) {
		  	NewPos.X += 1; 
		} else if (Move == KeyCodes.Down && NewPos.Y < Mat.size() - 1) {
		  	NewPos.Y += 1; 
		} else {
			ValidMove = false;
		}

		/*
		cout << "old pos" << Pos.X << " " << Pos.Y << endl;
		cout << "new pos" << NewPos.X << " " << NewPos.Y << endl;
		cout << ValidMove << endl; //*/

		if(ValidMove) {
			replacedChar = Mat[NewPos.Y][NewPos.X];
			Mat[NewPos.Y][NewPos.X] = Mat[Pos.Y][Pos.X];
			Mat[Pos.Y][Pos.X] = KEmpty;

			Pos = NewPos;
		}

		return replacedChar;
	} // MoveToken ()


	void ShowMatrix (const CMatrix & Mat) {
		BackgroundColor (CLR_RESET);
		Color (CLR_RESET);
		ClearScreen ();
		unsigned Width = 0;

		if (Mat.size () > 0) Width = Mat[0].size ();

		// Affichage d'une bordure
		Color (CLR_CYAN);
		for (unsigned i = 0; i < Width + 2; ++i) {
			cout << "#";
		}
		cout << endl;

		for (CVLine line : Mat) {
			Color (CLR_CYAN);
			cout << "#";
			for (char c : line) {
				switch (c) {
				  case KTokenPlayer1:
					Color (KColTokenP1);
					break;
				  case KTokenPlayer2:
					Color (KColTokenP2);
					break;
				  case KEmpty:
					Color (CLR_RESET);
					break;
				}
				cout << c;
			}
			Color (CLR_CYAN);
			cout << "#\n";
		}

		// Affichage d'une bordure
		Color (CLR_CYAN);
		for (unsigned i = 0; i < Width + 2; ++i) {
			cout << "#";
		}
		cout << endl;

		Color (CLR_RESET);
	} // ShowMatrix ()
}