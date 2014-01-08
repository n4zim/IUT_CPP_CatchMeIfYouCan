/*!
 * \file map.cxx
 * \author 
 * \date 08/01/14
 * \brief Map related functions prototypes
 * \version 1
 */

#include <string>
#include "globals.hxx"

#ifndef map_h 
#define map_h

namespace ChaseGame {
	/*!
	 * \brief Generate a random shape in the map
	 * \param Mat Game matrix
	 * \param Tab Shape
	 * \param y The y position
	 * \param x The x position
	 */
	void MatForm (CMatrix & Mat, array <bool,9> Tab, unsigned y, unsigned x);

	/*!
	 * \brief Creates game matrix from the parameters and config file
	 * \param Mat Game matrix
	 * \param Params Map parametes
	 */
	void GenMap (CMatrix & Mat, SMapGenParams Params);
	
	/*!
	 * \brief Displays game matrix
	 * \param Mat Game matrix
	 */
	void ShowMatrix (const CMatrix & Mat);


	/*!
	 * \brief Move a token in the game matrix
	 * \param Mat Game matrix
	 * \param Move Move code
	 * \param Pos Token position
	 * \return Replaced char
	 */
	char MoveToken (CMatrix & Mat, char Move, SPlayerPos & Pos, const SPlayerKeys& KeyCodes);
}

#endif
