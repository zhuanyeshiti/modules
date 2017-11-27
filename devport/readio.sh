#!/bin/bash

#for i in {1..10}
#for((i=1;i<100;i++))
#for i in 'seq 100'
i=10
while (( i ))
do
	echo $(./devport 0xf082 w)
	echo $(./devport 0xf084 w)

	echo $(./devport 0xf0c2 w)
	echo $(./devport 0xf0c4 w)

#	sleep 1
	let "i=i"
done


