# Kyle Tranfaglia - Cosc350 - Lab02 - Last updated: 09/18/23
#!/bin/bash

numArg=$#
num=$1
origin=$num
answer=0

if [ $numArg -ne 1 ];
then
	printf "This program only accepts one argument \n"
	exit 1
fi

while [ $num -gt 0 ]
do
	answer=`expr $num  % 10 + $answer`
	num=`expr $num / 10`
done

printf "The sum of %d is %d \n" $origin $answer
