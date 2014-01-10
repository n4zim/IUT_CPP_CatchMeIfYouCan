/*!
 *
 * \file unix.hxx
 * \author 
 * \date 08/01/14
 * \brief unix.cxx function prototypes
 * \version 1
 *
 * Defines UNIX specific functions
 * 
 */
 
#ifndef unix_h 
#define unix_h

namespace ChaseGame {
	/*!
	 * \brief Clears screen
	 */
	void ClearScreen ();

	/*!
	 * \brief Changes text color
	 * \param Color Wanted color
	 */
	void Color (const int& Color);

	/*!
	 * \brief Changes background color
	 * \param Color Wanted color
	 */
	void BackgroundColor (const int& Color);

	/*!
	 * \brief Captures a character from stdin
	 * \return captured character
	 */
	char GetInput ();

	/*!
	 * \brief Calls usleep
	 * \param MSec Microseconds to sleep
	 */
	void Sleep (int MSec);
}

#endif