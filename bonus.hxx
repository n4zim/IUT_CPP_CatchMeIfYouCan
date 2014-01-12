/*!
 * \file bonus.hxx
 * \author Peanut Butter Team
 * \date 10/01/14
 * \brief bonus.cxx function prototypes
 * \version 1
 */

#include <string>
#include "globals.hxx"

#ifndef bonus_h 
#define bonus_h

namespace ChaseGame {

	/*!
	 * \brief Applies an effect on the player
	 * \param GameStatus Game current status
	 * \param IsBonus Determines which type of effect to apply (true for bonus)
	 * \param IsP1 Determines who gets the effect (true for player one)
	 */
	void Effect (SGameStatus& GameStatus, bool IsBonus, bool IsP1);

	/*!
	 * \brief Swaps roles of two players
	 * \param GameStatus Game current status
	 */
	void BMSwap (SGameStatus & GameStatus);

	/*!
	 * \brief Stuns a player
	 * \param Player Player current status
	 */
	void MStun (SPlayerState& Player);

	/*!
	 * \brief Checks if a player is stunned and unstuns if it is time to do so
	 * \param Player Player current status
	 */
	void CheckStun(SPlayerState& Player);
}

#endif