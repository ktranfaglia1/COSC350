// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/20/23
// Header file to set up some constants and structs that will be used in multiple programs
#define NOT_READY -1
#define FILLED 0 // Sender filled data
#define TAKEN 1 // Receiver took data
#define GO 2 // Sender sending data
#define STOP 3 // Sender stop sending data

// Struct to hold integer pair
struct Integers{
	int int1;
	int int2;
};

// Struct for shared memory
struct Memory{
	int status;
	int gostop;
	struct Integers data;
};
