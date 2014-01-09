@echo off
del projet.exe
echo Compilation
g++ --std=c++11 -o projet.exe unix.cxx windows.cxx file.cxx map.cxx main.cxx -Wall
pause
projet.exe
color 08