#!/bin/bash

Aver=0
Temp=0
Am=0

while [ -n "$1" ]
do
let "Aver = Aver + $1"
let "Am = Am + 1"
shift
done

let "Aver = Aver / Am"

echo "AVERAGE:"$Aver
echo "AMOUNT:"$Am