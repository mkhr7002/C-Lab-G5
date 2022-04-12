#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include "derivative.h"
#include <hidef.h>
#define SERIAL_BUFFER 50

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
