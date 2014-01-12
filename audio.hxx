/*!
 * \file audio.hxx
 * \author Peanut Butter Team
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
	 * \param DoFade Do a crossfade
	 */
	void SetGameState (std::map <std::string, sf::Music&>& Tracks, int GameState, bool DoFade);

	/*!
	 * \brief Loads the songs and inits them
	 * \param Track1A Song
	 * \param Track1B Song
	 * \param Track1C Song
	 * \param Track2 Song
	 */
	void InitSongs (sf::Music& Track1A, sf::Music& Track1B, sf::Music& Track1C, sf::Music& Track2);


	/*!
	 * \brief Do a crossface between two songs
	 * \param A Song A
	 * \param B Song B
	 * \param VolumeA Wanted volume for song A
	 * \param VolumeB Wanted volume for song B
	 * \param FadeDuration Duration of the crossfade (in seconds)
	 */
	void DoubleSongVolumeFading (sf::Music& A, sf::Music& B, float VolumeA, float VolumeB, float FadeDuration);

	/*!
	 * \brief Do a crossface between three song
	 * \param A Song A
	 * \param B Song B
	 * \param C Song C
	 * \param VolumeA Wanted volume for song A
	 * \param VolumeB Wanted volume for song B
	 * \param VolumeC Wanted volume for song C
	 * \param FadeDuration Duration of the crossfade (in seconds)
	 */
	void TripleSongVolumeFading (sf::Music& A, sf::Music& B, sf::Music& C, float VolumeA, float VolumeB, float VolumeC, float FadeDuration);
}

#endif