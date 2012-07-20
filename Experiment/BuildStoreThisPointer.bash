#!/bin/bash
# Build StoringThisPointer experiment

g++ -g -o ../Object/StoringThisPointer StoringThisPointerFoo.cpp \
    StoringThisPointerBar.cpp StoringThisPointerDriver.cpp

