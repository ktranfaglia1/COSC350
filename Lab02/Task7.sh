# Kyle Tranfaglia - Cosc350 - Lab02 - Last updated: 09/18/23
#!/bin/bash

num=$1

count=1
answer=1
while [ "$count" -le "$num" ];
do
	answer=`expr $answer \* $count`
	let count++
done

printf "The factorial of %d is %d \n" $num $answer
