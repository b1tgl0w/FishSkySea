#!/bin/bash
#Builds all files regardless of their object files existing
#Use this when you don't want make to stop the build on error

#Add -Wall or -g if you want
g++ -o Object/BassDerby Source/*.cpp -lSDL -lSDL_image

