#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER


// function to intialise serial port

void initaliseSerialPorts (void);

// function to send "Initialisation Successful" to terminal via serial

void displaySuccessfulInit(int readData[]);

#endif