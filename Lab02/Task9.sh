# Kyle Tranfaglia - Cosc350 - Lab02 - Last updated: 09/18/23
#!/bin/bash

printf  "Enter a Directory: "
read directory

if [ ${directory:0:2}  = "~/" ];
then
	directory=$HOME${directory:1}
fi

if [ ! -d $directory ];
then
	printf "There is no directory named %s ... ending the program\n" "$directory"
	exit 1
fi

cd $directory

printf "Enter a readable file in the directory: %s: " "$directory"
read file

count=0
while  [ ! -e $file ];
do
	if [ $count -ge 2 ];
	then
		printf "Too many unrecognized files. Check your directory and try again ... ending the program\n"
		exit 2
	fi
	printf "Invalid file name! There is no file in %s named %s" "$directory" "$file"
	read file
	let count++
done

if [ ! -r $file ]; 
then
	printf "%s is a file but it is not readable ... ending the program\n" "$file"
	exit 3
fi

printf "Enter a word to find in the file: "
read word

if grep -q $word $file ;
then
	printf "%s FOUND!\n" "$word"
else
	printf "%s NOT FOUND\n" "$word"
	exit 4
fi

exit 0
