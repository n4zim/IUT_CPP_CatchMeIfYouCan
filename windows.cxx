/*!
 *
 * \file windows.cxx
 * \author 
 * \date 08/01/14
 * \brief Windows specific functions
 * \version 1
 *
 * Windows specific functions
 * 
 */

#include "globals.hxx"

#ifdef WINDOWS

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
 
namespace ChaseGame {
	void ClearScreen ()	{
		// http://msdn.microsoft.com/en-us/library/windows/desktop/ms682022%28v=vs.85%29.aspx

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coordScreen = { 0, 0 };    // home for the cursor 
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi; 
		DWORD dwConSize;

		// Get the number of character cells in the current buffer. 
		if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
			return;

		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

		// Fill the entire screen with blanks.
		if( !FillConsoleOutputCharacter( hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten ))
			return;

		// Get the current text attribute.
		if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
			return;

		// Set the buffer's attributes accordingly.

		if( !FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten )) 
			return;

		// Put the cursor at its home coordinates.
		SetConsoleCursorPosition( hConsole, coordScreen );
	}

	void Color (const int & coul) {
		if(coul != -1) {
	    	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), coul );
	    } else {
	    	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), KDefaultForeCol );
	    }
	}

	void BackgroundColor (const int & coul) {
		if(coul != -1) {
	    	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), coul*16 );
	    } else {
	    	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), KDefaultBackCol );
	    }
	}

	char GetInput () {
		return getch();
	}
}	
#endif
