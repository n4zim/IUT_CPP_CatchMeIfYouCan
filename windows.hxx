/*!
 *
 * \file windows.hpp
 * \author Josua Gonzalez
 * \date 07/01/14
 * \brief Defines Windows specific functions
 * \version 1
 *
 * Defines Windows specific functions
 * 
 */
 
#ifndef windows_h 
#define windows_h

namespace ChaseGame {
	#ifdef WINDOWS
		//! Windows color values
		enum ConsoleColors { CLR_BLACK=0, CLR_RED=4, CLR_GREEN=2, CLR_YELLOW=6, CLR_BLUE=1, CLR_MAGENTA=5, CLR_CYAN=2, CLR_GREY=8, CLR_WHITE=15, CLR_RESET=-1 };

		//! Windows default foreground color
		const int KDefaultForeCol = 8;

		//! Windows default background color
		const int KDefaultBackCol = 0;

		/*!
		 * \brief Clear screen
		 * Source MSDN : http://msdn.microsoft.com/en-us/library/windows/desktop/ms682022%28v=vs.85%29.aspx
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