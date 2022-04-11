#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include "derivative.h"
#include <hidef.h>
#define SERIAL_BUFFER 50

extern volatile int readCounter; // counter to use for reading in data from serial
extern volatile int writeCounter; // counter to use for writing in data from serial
extern volatile int READ_WRITE; // constant used to determine whether the port will be reading/writing
extern volatile int carriageFlag; // constant used to determine end of string

static volatile char rawData[SERIAL_BUFFER]; // list to store characters which are read/sent

typedef struct serialPort{ 
  byte *BaudHigh;
  byte *BaudLow;
  byte *ControlRegister1;
  byte *ControlRegister2;
  byte *DataRegister;
  byte *StatusRegister;
} serialPort;

// function to intialise serial port

void initialiseSerialPort (serialPort *serial_port);

// function to send "Initialisation Successful" to terminal via serial

void writeStringToSCI(serialPort *serial_port, char* string);

// function to convert the global array from serial.h into a non-global
// array which can be modified and used in main.c

// function to read serial data and store in array
void readSerial(serialPort *serial_port);

void writeSerial(serialPort *serial_port);

// reset everything so new input can be received
void resetNewInput(void);

void processSerialInput(void);

#endif
