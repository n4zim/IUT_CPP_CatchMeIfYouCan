/*!
 *
 * \file bonus.cxx
 * \author 
 * \date 10/01/14
 * \brief File related bonus and malus
 * \version 1
 *
 * Contains functions that creates bonuses and maluses in the map
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "globals.hxx"
#include "map.hxx"

using namespace std;

namespace ChaseGame {

	void Effect (CMatrix & Mat, SGameStatus& GameStatus, bool IsBonus, bool IsP1) {
		if (IsP1) {
			if (IsBonus) {
				cout << "Bonus joueur 1";
			} else {
				cout << "Malus joueur 1";
			}
		} else {
			if (IsBonus) {
				cout << "Bonus joueur 2";
			} else {
				cout << "Malus joueur 2";
			}
		}
	}

}