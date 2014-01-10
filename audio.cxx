/*!
 *
 * \file game.cxx
 * \author 
 * \date 09/01/14
 * \brief Audio related functions
 * \version 1 
 */


#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <time.h> 
#include <stdlib.h>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include "globals.hxx"

using namespace std;

namespace ChaseGame {
	void SetGameState (map <string, sf::Music&>& Tracks, int GameState) {
		switch (GameState) {
		  case GMS_TITLE:
		  	try {
			  	Tracks.at("A1").SetVolume(80.0f);
			  	Tracks.at("B1").SetVolume(0.0f);
			  	Tracks.at("C1").SetVolume(0.0f);
			  	Tracks.at("2").SetVolume(0.0f);
			} catch (out_of_range) {
				cerr << "Error switching music";
			}
			break;
		  case GMS_STARTING:
		  	try {
			  	Tracks.at("A1").SetVolume(0.0f);
			  	Tracks.at("B1").SetVolume(70.0f);
			  	Tracks.at("C1").SetVolume(0.0f);
			  	Tracks.at("2").SetVolume(0.0f);
			} catch (out_of_range) {
				cerr << "Error switching music";
			}
			break;
		  case GMS_INGAME:
		  	try {
			  	Tracks.at("A1").SetVolume(0.0f);
			  	Tracks.at("B1").SetVolume(0.0f);
			  	Tracks.at("C1").SetVolume(70.0f);
			  	Tracks.at("2").SetVolume(80.0f);
			} catch (out_of_range) {
				cerr << "Error switching music";
			}
			break;
		}
	}
}