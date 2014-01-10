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
#include "audio.hxx"

using namespace std;

namespace ChaseGame {
	void SetGameState (map <string, sf::Music&>& Tracks, int GameState, bool DoFade) {
		switch (GameState) {
		  case GMS_TITLE:
		  	try {
			  	Tracks.at("C1").SetVolume(0.0f);
			  	Tracks.at("2").SetVolume(0.0f);

			  	if(DoFade)
			  		DoubleSongVolumeFading (Tracks.at("A1"), Tracks.at("B1"), 80.0f, 0.0f, 0.5f);
			  	else {
			  		Tracks.at("A1").SetVolume(80.0f);
			  		Tracks.at("B1").SetVolume(0.0f);
			  	}
			} catch (out_of_range) {
				cerr << "Error switching music" << endl;
			}
			break;
		  case GMS_STARTING:
		  	try {
			  	Tracks.at("C1").SetVolume(0.0f);
			  	Tracks.at("2").SetVolume(0.0f);

			  	if(DoFade)
			  		DoubleSongVolumeFading (Tracks.at("A1"), Tracks.at("B1"), 0.0f, 70.0f, 0.5f);
			  	else {
				  	Tracks.at("A1").SetVolume(0.0f);
				  	Tracks.at("B1").SetVolume(70.0f);
			  	}
			} catch (out_of_range) {
				cerr << "Error switching music" << endl;
			}
			break;
		  case GMS_INGAME:
		  	try {
			  	Tracks.at("A1").SetVolume(0.0f);

			  	if(DoFade) {
			  		TripleSongVolumeFading (Tracks.at("B1"), Tracks.at("C1"), Tracks.at("2"), 0.0f, 70.0f, 80.0f, 0.5f);
			  	} else {
				  	Tracks.at("B1").SetVolume(0.0f);
				  	Tracks.at("C1").SetVolume(100.0f);
			  		Tracks.at("2").SetVolume(80.0f);
			  	}
			} catch (out_of_range) {
				cerr << "Error switching music" << endl;
			}
			break;
		}
	}

	void InitSongs (sf::Music& Track1A, sf::Music& Track1B, sf::Music& Track1C, sf::Music& Track2) {		
		Track1A.OpenFromFile("sound/bgm_trackA-1.ogg");
		Track1B.OpenFromFile("sound/bgm_trackA-2.ogg");
		Track1C.OpenFromFile("sound/bgm_trackA-3.ogg");
		Track2.OpenFromFile("sound/bgm_trackB.ogg");
		Track1A.SetLoop(true);
		Track1B.SetLoop(true);
		Track1C.SetLoop(true);
		Track2.SetLoop(true);
		Track1A.Play();
		Track1B.Play();
		Track1C.Play();
		Track2.Play();
	}

	void DoubleSongVolumeFading (sf::Music& A, sf::Music& B, float VolumeA, float VolumeB, float FadeDuration) {
		int SleepDuration = 1000;
		sf::Clock Clock;
		float VolumeDiffA = VolumeA - A.GetVolume ();
		float VolumeDiffB = VolumeB - B.GetVolume ();

		Clock.Reset ();
		for(;;) {
			Sleep (SleepDuration);

			A.SetVolume (Clock.GetElapsedTime () / FadeDuration * VolumeDiffA);
			B.SetVolume (Clock.GetElapsedTime () / FadeDuration * VolumeDiffB);

			if(Clock.GetElapsedTime () > FadeDuration)
				break;

			//cout << Clock.GetElapsedTime () << endl;
		}


		A.SetVolume (VolumeA);
		B.SetVolume (VolumeB);
	}

	void TripleSongVolumeFading (sf::Music& A, sf::Music& B, sf::Music& C, float VolumeA, float VolumeB, float VolumeC, float FadeDuration) {
		int SleepDuration = 1000;
		sf::Clock Clock;
		float VolumeDiffA = VolumeA - A.GetVolume ();
		float VolumeDiffB = VolumeB - B.GetVolume ();
		float VolumeDiffC = VolumeC - C.GetVolume ();

		Clock.Reset ();
		for(;;) {
			Sleep (SleepDuration);

			A.SetVolume (Clock.GetElapsedTime () / FadeDuration * VolumeDiffA);
			B.SetVolume (Clock.GetElapsedTime () / FadeDuration * VolumeDiffB);
			C.SetVolume (Clock.GetElapsedTime () / FadeDuration * VolumeDiffC);

			if(Clock.GetElapsedTime () > FadeDuration)
				break;

			//cout << Clock.GetElapsedTime () << endl;
		}

		A.SetVolume (VolumeA);
		B.SetVolume (VolumeB);
		C.SetVolume (VolumeC);
	}
}