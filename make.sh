#!/bin/bash
rm projet *.o
clear

echo Starting compilation
g++ --std=c++11 -c unix.cxx audio.cxx file.cxx map.cxx game.cxx banana.cxx main.cxx -Wall

echo Linking SFML 1.6 library
g++ --std=c++11 -o projet unix.o audio.o file.o map.o game.o banana.o main.o -lsfml-system -lsfml-audio

./projet
