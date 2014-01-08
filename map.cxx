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

using namespace std;

namespace ChaseGame {


	void MatForm (CMatrix & Mat, array <bool,9> Tab, unsigned y, unsigned x) {

		// Coordonnées des points de forme
		array <int,9> coordy = {0,0,0, 1,1,1, 2,2,2};
		array <int,9> coordx = {0,1,2, 0,1,2, 0,1,2};

		for(unsigned i = 0; i < coordy.size(); i++)	
			if(Tab[i])
				Mat[y + coordy[i]][x + coordx[i]] = KObstacle;
			else
				Mat[y + coordy[i]][x + coordx[i]] = KEmpty;

		// Coordonnées des espacements
		array <int,8> spacey = {0,1,2,3, 3,3,3,3};
		array <int,8> spacex = {3,3,3,3, 0,1,2,3};

		for(unsigned i = 0; i < spacey.size(); i++)
			Mat[y + spacey[i]][x + spacex[i]] = KEmpty;
	}


	void GenMap (CMatrix & Mat, SMapGenParams Params) {

		for (unsigned i = 0; i < Params.MapHeight; ++i) {
			CVLine Line;
			for (unsigned j = 0; j < Params.MapWidth; ++j) {
				Line.push_back (KEmpty);
			}
			Mat.push_back (Line);
		}


		// [UPDATE] Nazim - 09:12
		
			// Génère un nombre aléatoire pour le nombre d'obstacles
			unsigned nbobst = rand() % 8 + 4;
			
			// Déclaration de variables
			unsigned forme;
			unsigned x;
			unsigned y;

			for (unsigned i = 0; i < nbobst; i++) {
			
				// Choix aléatoire de la forme (ETAPE 1)
				forme = rand() % 7 + 1;

				// Choix aléatoire de la position (ETAPE 2)
				bool passable = false;
				while (!passable) {

					// Génération aléatoire des coordonnées des obstacles depuis la taille de la map (3 de marge)
					x = rand() % (Params.MapWidth - 3);
					y = rand() % (Params.MapHeight - 3);
					
					if (Mat[y][x]		== KEmpty &&
						Mat[y+1][x] 	== KEmpty &&											
						Mat[y+2][x] 	== KEmpty &&
						Mat[y][x+1] 	== KEmpty &&
						Mat[y+1][x+1] 	== KEmpty &&		
						Mat[y+2][x+1] 	== KEmpty)
							passable = true;
				}

				// Mise en place de l'obstacle (ETAPE 3)
               	switch (forme) {
                    case 1:
                        MatForm (Mat, { 0, 1, 0,
                        		        1, 1, 1,
                        		        0, 1, 0 }, y, x);
                        break;
                    // Barre
                    case 2:
                        MatForm (Mat, { 0, 1, 0,
                        		        0, 1, 0,
                        		        0, 1, 0 }, y, x);
                        break;
                    // L
                    case 3:
                        MatForm (Mat, { 1, 0, 0,
                        		        1, 0, 0,
                        		        1, 1, 1 }, y, x);
                        break;
                    // Point
                    case 4:
                        MatForm (Mat, { 0, 0, 0,
                        		        0, 1, 0,
                        		        0, 0, 0 }, y, x);
                        break;
                    // |-
                    case 5:
                        MatForm (Mat, { 1, 0, 0,
                        		        1, 1, 1,
                        		        1, 0, 0 }, y, x);
                        break;
                    // Point
                    case 6:
                        MatForm (Mat, { 0, 0, 0,
                        		        0, 1, 0,
                        		        0, 0, 0 }, y, x);
                        break;
                    // +
                    case 7:
                        MatForm (Mat, { 0, 1, 0,
                        		        1, 1, 1,
                        		        0, 1, 0 }, y, x);
                        break;
                }
            }

		// [/UPDATE]    

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
		//ClearScreen ();
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
