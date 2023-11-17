// Kyle Tranfaglia
// COSC350 - Lab04
// Last Updated 10/09/23
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1

// Prototypes
void err_sys(char*);
int myAtoi(char*);
void myItoa(char*, int);

int main(int argc, char* argv[]) {
	// Input validation check for number of arguments
	if (argc != 2) {
		err_sys("Invalid number of arguments ... only accepts one argument");
	}
	int inFile = open(argv[1], O_RDONLY);
	// Validates that the input file opened
	if (inFile == -1) {
		err_sys("Open file error");
	}
	// Variables
	int integer = 0, num = 0, bytes = 0;
	char buffer[BUFFER_SIZE], data1[80];
	// Loop to concatentate a char array of only numbers from the buffered input
	while ((bytes = read(inFile, buffer, BUFFER_SIZE)) > 0) {
		if (buffer[0] <= '9' && buffer[0] >= '0') {
			data1[num++] = buffer[0];
		}
	}

	// Read error check
	if (bytes == -1) {
		err_sys("Read Error");
	}

	// Convert to an integer with function call and add 10
	integer = myAtoi(data1);
	integer += 10;
	// Convert back to a string by passing char array as parameter
	myItoa(data1, integer);

	// Write the string to standard out and error check
	if (write(1, data1, strlen(data1)) == -1)
		err_sys("Write Error");

	printf("\nString as an Integer: %d\n", integer); // Prints the integer value to terminal

	exit(0);
}
// Error fucntion
void err_sys(char *str) {
	printf("%s\n", str);
	exit(1);
}

// Convertion function -  string to integer - Does not deal with negatives
int myAtoi(char *str) {
	int result = 0;

	// Loop to run for as long as integers are read in
	while (*str <= '9' && *str >= '0') {
		result = result*10 + (*str - '0');
		str++;
	}

	return result;
}
// Convertion function - integer to a character array - Adds endline character to end
void myItoa(char *str, int integer) {
	int temp = integer, count = 0;
	// Loop to get size with decimal base ten division
    	while (temp > 0) {
        	temp /= 10;
        	count++;
    	}
	// Loop to convert the integer to character array by using decimal modular arithmetic to convert each integer to a char 
	for (int i = count - 1; i >= 0; i--) {
        	str[i] = (integer % 10) + '0';
        	integer /= 10;
    	}
	str[count] = '\0'; // Adds endline character to string
}
