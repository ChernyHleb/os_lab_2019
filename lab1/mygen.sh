#!/bin/bash
VAR=1
echo -n > numbers.txt
until [[ "$VAR" -eq 151 ]]
do
echo $RANDOM >> numbers.txt
let "VAR = VAR + 1"
done