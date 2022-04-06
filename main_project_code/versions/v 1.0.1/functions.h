#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#define SERIAL_BUFFER 30

static int readCounter = 0; // counter to use for reading in data from serial
static int writeCounter = 0; // counter to use for writing in data from serial
static int READ_WRITE = 0; // constant used to determine whether the port will be reading/writing
static int carriageFlag = 0; // constant used to determine end of string


static char rawData[SERIAL_BUFFER]; // list to store characters which are read/sent

// function to intialise serial port

void initialiseSerialPorts (void);

// function to send "Initialisation Successful" to terminal via serial

void displaySuccessfulInit(int data[]);

// function to convert the global array from serial.h into a non-global
// array which can be modified and used in main.c

// function to read serial data and store in array
void readSerial(int port);

void writeSerial(int port);

// reset everything so new input can be received
void resetNewInput(void);

void processSerialInput(void);

#endif
