#!/bin/bash

echo "enter the number"
read numbr

space=$((numbr - 1))
i=1
while [ $i -le $numbr ]
do
    j=1
    while [ $j -le $space ]
    do
        echo -n " "
        j=$((j + 1))
    done
    j=1
    while [ $j -le $((2*i-1)) ]
    do
        echo -n "*"
        j=$((j + 1))
    done
    echo
    space=$((space-1))
    i=$((i + 1))
done
