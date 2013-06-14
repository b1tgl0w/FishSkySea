#!/bin/bash

if make 2> BuildLog; then
    cd Object
    ./SeaBassShowdown
    cd ..
else
    vim BuildLog
fi

