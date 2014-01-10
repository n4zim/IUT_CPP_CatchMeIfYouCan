/*!
 * \file audio.hxx
 * \author 
 * \date 09/01/14
 * \brief audio.cxx function prototypes
 * \version 1
 */

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include "globals.hxx"

#ifndef audio_h 
#define audio_h

namespace ChaseGame {	
	/*!
	 * \brief Sets music volumes according to the game state
	 * \param Tracks Music map
	 * \param GameState from the GameMusicState enum
	 */
	void SetGameState(std::map <std::string, sf::Music&>& Tracks, int GameState);
}

#endif