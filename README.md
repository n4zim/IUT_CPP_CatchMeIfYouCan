README
========

You need to install SFML 1.6 lib to be able to compile.
Exemple of installation command for ubuntu 13.10 : 
sudo apt-get install mesa-common-dev ibglu-dev
sudo apt-get install libsfml-dev

COMPILING
--------

After you installed the SFML 1.6 lib, you can compile it using the commands:

g++ --std=c++11 -c unix.cxx audio.cxx file.cxx map.cxx game.cxx banana.cxx bonus.cxx main.cxx -Wall

and

g++ --std=c++11 -o projet unix.o audio.o file.o map.o game.o bonus.o banana.o main.o -lsfml-system -lsfml-audio

SOUND CREDIT
--------

Validation sound effect by broumbroum, under a creative commons 3.0 by licence
http://www.freesound.org/people/broumbroum/sounds/50565/

Game music is "Trickyness" under CC BY licence by Josua Gonzalez
https://soundcloud.com/josuag/trickyness-wip

See CHANGES.md to see changes of the project (in french)