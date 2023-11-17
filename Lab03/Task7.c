// Kyle Tranfaglia
// COSC 350 - Lab03
// Last Updated 10/02/23
#include <stdio.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <unistd.h>
// Error Function
void err_sys(char *str) {
    printf("%s\n",str);
    exit (1);
}
int strToInt(char *str) {
	// Loop to capture spacing and move along
	while (*str == ' ' || *str == '\t')
		str++;

	int result = 0, sign = 1; // Variables
	// Checks if subtraction and initiates sign change
	if (*str == '-') {
		sign = -1;
		str++;
	}
	else if (*str == '+') { // If addittion sign, ignore
		str++;
	}
	// Loop to convert characters that are numbers 0-9 to integers with ASCII values
	while(*str <= '9' && *str >= '0') {
		result = result*10 + (*str - '0');
		str++;
	}

	return result * sign;
}

int main(int argc, char *argv[]) {
	// Checks that at least one argument was given
	if (argc < 1) {
		err_sys("No arguments given");
	}

	int sum = 0;
	// Loops through the entire array of arguments
	for (int i = 0; i < argc; i++){
		sum += strToInt(argv[i]);
	}

	printf("%d\n", sum); // prints resulting sum

	exit (0);
}
