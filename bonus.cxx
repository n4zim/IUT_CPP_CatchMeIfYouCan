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

        if (IsBonus) {
                cout << "isbonus init random effect"; // test
                if ((rand() % 100) > 10)
                        BMSwap();
                else
                        BStun();
        }
        else
        {
                MStun();
        }
    }
 
    void MStun()
    {
            /*
                    sf::Clock Clock;
                    Clock.Reset();
                    Clock.GetElapsedTime();

                    Auto blocage.
            */
    }

    void BStun()
    {
            /*
                    sf::Clock Clock;
                    Clock.Reset();
                    Clock.GetElapsedTime();

                    Bloquer le joueur adverse
            */
    }

    void BMSwap()
    {
            // Sans effet ? pk ?
            swap(GameStatus.P1.IsChasing, GameStatus.P2.IsChasing);

    }

}