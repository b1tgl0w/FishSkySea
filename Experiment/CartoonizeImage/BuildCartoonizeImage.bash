#!/bin/bash

g++ -pg -o ../../Object/CartoonizeImage CartoonizeImage.cpp ../../Source/Math.cpp ../../SharedSource/PaletteHarmony/Color.cpp -lSDL -lSDL_image

