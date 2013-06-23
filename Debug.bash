#!/bin/bash
#Builds and runs SBS
#If there is at least one object file that has debug symbols, cleans first

mustClean=0
for f in Object/*.o; do
    debug=`nm -a $f | grep -c " N "`
    if [ "$debug" = 0 ]; then
        mustClean=1
    fi
done

if [ $mustClean = 1 ]; then
    make clean
fi

if make debug 2> BuildLogUUID1122; then
    cd Object
    gdb SeaBassShowdown -ex=run
    cd ..
else
    vim BuildLogUUID1122
fi

rm BuildLogUUID1122

