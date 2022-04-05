#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#define SERIAL_BUFFER 30

static int readCounter = 0; // counter to use for reading in data from serial
static int writeCounter = 0; // counter to use for writing in data from serial
static int READ_WRITE = 0; // constant used to determine whether the port will be reading/writing


static char rawData[SERIAL_BUFFER]; // list to store characters which are read/sent

// function to intialise serial port

void initialiseSerialPorts (void);

// function to send "Initialisation Successful" to terminal via serial

void displaySuccessfulInit(int data[]);

// function to convert the global array from serial.h into a non-global
// array which can be modified and used in main.c

#endif
