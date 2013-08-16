#!/bin/bash

for myfile in Source/*cpp; do grep -l $1  $myfile | sed s/Source/Header/ \
| sed s/cpp/hpp/; grep -l $1 $myfile; done

