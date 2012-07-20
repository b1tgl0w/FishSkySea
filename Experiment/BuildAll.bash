#!/bin/bash
shopt -s extglob
DIR="$( cd -P "$( dirname "$0" )" && pwd )"
for i in !(*All*|!(Build*.bash)); do
    bash "$DIR"/$i #Warning unknown danger if no Build*.bash files
done

