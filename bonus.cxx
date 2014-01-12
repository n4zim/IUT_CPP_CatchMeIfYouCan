/*!
 *
 * \file bonus.cxx
 * \author
 * \date 10/01/14
 * \brief File related bonus and malus
 * \version 1
 *
 * Contains functions that take actions when a bonus/malus is triggered
 *
 */
 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include "bonus.hxx"
 
#include "globals.hxx"
#include "map.hxx"
 
using namespace std;
 
namespace ChaseGame { 
    void Effect (SGameStatus& GameStatus, bool IsBonus, bool IsP1) {
        if (IsBonus == true) { // swaps the roles
            BMSwap (GameStatus);
        } else { // stuns the opponant
            if(IsP1)
            	MStun (GameStatus.P2);
            else
            	MStun (GameStatus.P1);
        }
    }

    void MStun(SPlayerState& Player) {
        Player.IsStunned = true;
        Player.StunDuration = rand () % 25 + 5;
    }

    void CheckStun(SPlayerState& Player) {
        if(Player.IsStunned) {
        	if(Player.StunDuration > 0)
        		--Player.StunDuration;
        	else
        		Player.IsStunned = false; 
        }
    }

    void BMSwap(SGameStatus & GameStatus) {
    	ClearScreen ();
    	cout << "\n\n " << GameStatus.LocaleStr.MsgRolesSwapped << endl;

        GameStatus.P1.IsChasing = !GameStatus.P1.IsChasing;
        GameStatus.P2.IsChasing = !GameStatus.P2.IsChasing;

		// Display new roles
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
    } 
}