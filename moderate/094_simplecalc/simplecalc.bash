#!/usr/bin/env bash

# $1 is arg 1
LINES="$(cat $1 | wc -l)"

for i in `seq 1 $LINES`;	
do
	printf "%.5f\n" "$(bc -l <<< "$(sed -n ${i}p $1)")" | sed 's/0\+$//;s/\.$//'
done
