#!/bin/bash

g++ -pg -o ../../Object/MessageBox Source/Driver.cpp Header/MessageBoxLine.hpp Source/MessageBoxLine.cpp -lSDL -lSDL_image -lSDL_ttf

