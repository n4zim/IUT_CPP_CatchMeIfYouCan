/*!
 * \file map.hxx
 * \author 
 * \date 08/01/14
 * \brief map.cxx function prototypes
 * \version 1
 */

#include <string>
#include <array>
#include "globals.hxx"

#ifndef map_h 
#define map_h

namespace ChaseGame {

	/*!
	 * \brief Generate a random shape in the map
	 * \param Mat Game matrix
	 * \param Tab Shape
	 * \param Y The y position
	 * \param X The x position
	 */
	void MatShape (CMatrix & Mat, const std::array <bool, 9> Tab, const unsigned Y, const unsigned X);

	/*!
	 * \brief Creates game matrix from the parameters and config file
	 * \param Mat Game matrix
	 * \param Params Map parametes
	 * \param Difficulty Game difficulty (higher => more obstacles)
	 */
	void GenMap (CMatrix & Mat, const SMapGenParams& Params, const int Difficulty);
	
	/*!
	 * \brief Displays game matrix
	 * \param Mat Game matrix
	 * \param ColorSet Colors to use
	 */
	void ShowMatrix (const CMatrix & Mat, const SColorSet& ColorSet);


	/*!
	 * \brief Move a token in the game matrix
	 * \param Mat Game matrix
	 * \param Move Move code
	 * \param Player Player data
	 * \param KeyCodes Player specific key codes for movement
	 * \return Replaced char
	 */
	char MoveToken (CMatrix & Mat, const char Move, SPlayerState & Player, const SPlayerKeys& KeyCodes);

	/*!
	 * \brief Random between min and max
	 * \param Min minimum
	 * \param Max maximum
	 * \return A random value
	 */
	unsigned RRand (unsigned Min, unsigned Max);

	/*!
	 * \brief Display bonus
	 * \param Mat Game matrix
	 */
	void GenBonusMalus (CMatrix & Mat);
}

#endif
