#!/bin/bash

g++ -Wall -o ../../Object/SharedPtrFactoryStoreAsBase Source/Container.cpp \
    Source/DerivedFoo.cpp Source/DerivedBar.cpp Source/SharedPtrFactoryStoreAsBase.cpp

