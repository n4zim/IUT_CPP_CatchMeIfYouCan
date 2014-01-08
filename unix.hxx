/*!
 *
 * \file unix.hpp
 * \author 
 * \date 08/01/14
 * \brief Defines UNIX specific functions
 * \version 1
 *
 * Defines UNIX specific functions
 * 
 */
 
#ifndef unix_h 
#define unix_h

namespace ChaseGame {
	#ifdef UNIX
		//! Unix color values
		enum ConsoleColors { CLR_BLACK=30, CLR_RED=31, CLR_GREEN=32, CLR_YELLOW=33, CLR_BLUE=34, CLR_MAGENTA=35, CLR_CYAN=36, CLR_WHITE=37, CLR_GREY=30, CLR_RESET=0 };

		/*!
		 * \brief Clear screen
		 */
		void ClearScreen ();

		/*!
		 * \brief Changes text color
		 * \param coul Wanted color
		 */
		void Color (const int&);

		/*!
		 * \brief Changes background color
		 * \param coul Wanted color
		 */
		void BackgroundColor (const int&);

		/*!
		 * \brief Captures a character from stdin
		 * \return captured character
		 */
		char GetInput ();
	#endif
}

#endif