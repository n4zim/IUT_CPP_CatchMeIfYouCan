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

	unsigned RRand (unsigned Min, unsigned Max)
	{
	    return rand() % (Max - Min) + Min;
	}	

	void GenBonus_Malus (CMatrix & Mat)
	{
		/*
			{Bonus} Warp mur  			= ¤
			{Bonus/Malus} Swap de rôle  = $
			{Bonus} Stun  				= %
			{Malus} Stun				= £
			{Autres à voir...}
		*/

		string Bonus = "¤$%";
		string Malus = "£";

		unsigned y = RRand(0, Mat.size());
		unsigned x = RRand(0, Mat[y].size());

		if ((rand() % 100) > 98 && Mat[y][x] == KEmpty)
		{
			unsigned chance = RRand(0, 1);
			if (chance == 0)
				Mat[y][x] = Bonus[RRand(0, Bonus.size())];
			else
				Mat[y][x] = Malus[RRand(0, Malus.size())];
		}
	} // GenBonus_Malus ()

	void Effect (CMatrix & Mat, SPlayerPos Player)
	{
		// A finir
	}

}