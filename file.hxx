/*!
 * \file file.hxx
 * \author 
 * \date 08/01/14
 * \brief file.cxx function prototypes
 * \version 1
 */

#include <string>
#include "globals.hxx"

#ifndef file_h 
#define file_h

namespace ChaseGame {	
	/*!
	 * \brief Loads parameters from a config file
	 * \param FileName Config filename
	 * \return Map generator parametors loaded from file or default config
	 */
	SMapGenParams LoadMapGenConfig (const std::string & FileName);

	/*!
	 * \brief Saves parameters in a config file
	 * \param FileName Config filename
	 * \param Params Map config to write in the file
	 * \return true if write was successfull,
	 * \return false if write error
	 */
	bool SaveMapConfig (const std::string& FileName, SMapGenParams& Params);
	
	/*!
	 * \brief Loads game configuration
	 * \return Game configuration structure loaded from file or default config
	 */
	SGameStatus LoadGameConfig (const std::string & FileName);

	/*!
	 * \brief Saves game configuration in a config file
	 * \param FileName Config filename
	 * \param Config Config to write in the file
	 * \return true if write was successfull
	 * \return false if write error
	 */
	bool SaveGameConfig (const std::string& FileName, SGameStatus& Config);
}

#endif