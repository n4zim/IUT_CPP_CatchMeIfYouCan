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
#include <array>

#include "globals.hxx"
#include "windows.hxx" 
#include "unix.hxx"
#include "map.hxx"

using namespace std;

namespace ChaseGame {
	void MatShape (CMatrix & Mat, const array <bool, 9> Tab, const unsigned Y, const unsigned X) {
		// Shape figures coordinates
		array <int, 9> CoordY = {0, 0, 0, 1, 1, 1, 2, 2, 2}; // c++ 11 {r,o,c,k,s} \o/
		array <int, 9> CoordX = {0, 1, 2, 0, 1, 2, 0, 1, 2};

		for (unsigned i = 0; i < CoordY.size(); i++)	{
			if(Tab[i])
				Mat[Y + CoordY[i]][X + CoordX[i]] = KObstacle;
			else
				Mat[Y + CoordY[i]][X + CoordX[i]] = KEmpty;
		}

		// Spacing coordinates
		array <int, 8> SpaceY = {0, 1, 2, 3, 3, 3, 3, 3};
		array <int, 8> SpaceX = {3, 3, 3, 3, 0, 1, 2, 3};

		for (unsigned i = 0; i < SpaceY.size(); i++) {
			Mat[Y + SpaceY[i]][X + SpaceX[i]] = KEmpty;
		}
	} // MatShape ()


	void GenMap (CMatrix & Mat, const SMapGenParams& Params, const int Difficulty) {
		// Generate an empty array
		for (unsigned i = 0; i < Params.MapHeight; ++i) {
			CVLine Line;
			for (unsigned j = 0; j < Params.MapWidth; ++j) {
				Line.push_back (KEmpty);
			}
			Mat.push_back (Line);
		}

		// Determine number of shapes to generate
		unsigned NbObst = 0;

		switch (Difficulty) {
		  case DIFFLVL_EASY:
			NbObst = rand() % 4 + 2;
			break;
		  case DIFFLVL_NORM:
			NbObst = rand() % 8 + 4;
			break;
		  case DIFFLVL_HARD:
			NbObst = rand() % 15 + 6;
			break;
		  case DIFFLVL_CRZY:
			NbObst = rand() % 20 + 10;
			break;
		}

		// Generate the shapes
		for (unsigned i = 0; i < NbObst; i++) {
			// Choosing shape (STEP 1)
			//unsigned Shape = ;

			unsigned X, Y;

			// Choosing position (STEP 2)
			for( ; ; ) {
				// Random generation of shapes coords from map size and 3 cells offset
				X = rand() % (Params.MapWidth - 3);
				Y = rand() % (Params.MapHeight - 3);
				
				// Detect if the cells are empty and if so stop coordinates generation
				if (Mat[Y][X]   == KEmpty && Mat[Y+1][X]   == KEmpty && Mat[Y+2][X]   == KEmpty &&
					Mat[Y][X+1] == KEmpty && Mat[Y+1][X+1] == KEmpty && Mat[Y+2][X+1] == KEmpty)
					break;
			}

			// Place the shape (STEP 3)

			// Generate a random shape number [1-7] and create it using MatShape
           	switch (rand() % 7 + 1) {
           		// Shape : +
                case 1:
                    MatShape (Mat, { 0, 1, 0, 
                    		        1, 1, 1, 
                    		        0, 1, 0 }, Y, X);
                    break;
                // Shape : |
                case 2:
                    MatShape (Mat, { 0, 1, 0, 
                    		        0, 1, 0, 
                    		        0, 1, 0 }, Y, X);
                    break;
                // Shape : L
                case 3:
                    MatShape (Mat, { 1, 0, 0, 
                    		        1, 0, 0, 
                    		        1, 1, 1 }, Y, X);
                    break;
                // Shape : Dot
                case 4:
                case 6:
                    MatShape (Mat, { 0, 0, 0, 
                    		        0, 1, 0, 
                    		        0, 0, 0 }, Y, X);
                    break;
                // Shape : |-
                case 5:
                    MatShape (Mat, { 1, 0, 0, 
                    		        1, 1, 1, 
                    		        1, 0, 0 }, Y, X);
                    break;
                // Shape : +
                case 7:
                    MatShape (Mat, { 0, 1, 0, 
                    		        1, 1, 1, 
                    		        0, 1, 0 }, Y, X);
                    break;
            }
        }

        // Placing the players in the grid
		Mat[Params.PosPlayer1.Y][Params.PosPlayer1.X] = KTokenPlayer1;
		Mat[Params.PosPlayer2.Y][Params.PosPlayer2.X] = KTokenPlayer2;
	} // GenMap ()


	char MoveToken (CMatrix & Mat, const char Move, SPlayerPos & Pos, const SPlayerKeys& KeyCodes) {
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
			return KEmpty; // We cancel the movement by stopping the function
		}

		if(Mat[NewPos.Y][NewPos.X] == KObstacle) // Prevent player from walking into walls
			return KEmpty; // Cancel movement

		replacedChar = Mat[NewPos.Y][NewPos.X];
		Mat[NewPos.Y][NewPos.X] = Mat[Pos.Y][Pos.X];
		Mat[Pos.Y][Pos.X] = KEmpty;

		Pos = NewPos;

		return replacedChar;
	} // MoveToken ()


	void ShowMatrix (const CMatrix & Mat, const SColorSet& ColorSet) {
		// Reset screen colors and clear it
		BackgroundColor (CLR_RESET);
		Color (CLR_RESET);

		unsigned Width = 0;
		if (Mat.size () > 0)
			Width = Mat[0].size ();

		// Display top map border
		Color (ColorSet.ColorWall);
		for (unsigned i = 0; i < Width + 2; ++i) {
			cout << KObstacle;
		}
		cout << endl;

		// Display the matrix (plus left/right borders)
		for (CVLine line : Mat) {
			Color (ColorSet.ColorWall);
			cout << "#";
			for (char c : line) {
				switch (c) {
				  case KTokenPlayer1:
					Color (ColorSet.ColorP1);
					break;
				  case KTokenPlayer2:
					Color (ColorSet.ColorP2);
					break;
				  case KObstacle:
				  	Color (ColorSet.ColorObstacle);
				  	break;
				  case KEmpty:
					Color (CLR_RESET);
					break;
				}
				cout << c;
			}
			Color (ColorSet.ColorWall);
			cout << KObstacle << "\n";
		}

		// Display bottom map border
		Color (ColorSet.ColorWall);
		for (unsigned i = 0; i < Width + 2; ++i) {
			cout << KObstacle;
		}
		cout << endl;

		Color (CLR_RESET);

	} // ShowMatrix ()
}
