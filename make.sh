#!/bin/bash
rm projet
clear
echo Starting compilation
g++ --std=c++11 -o projet unix.cxx windows.cxx file.cxx map.cxx game.cxx main.cxx -Wall
echo Program compiled, starting
./projet
