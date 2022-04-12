#include "string.h"
#include "functions.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */
#include <hidef.h>
// set up the serial ports

void initialiseSerialPort(serialPort *serial_port) {
  
  *(serial_port->BaudHigh)=0;   // set baud rate
  *(serial_port->BaudLow)=156; 
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_RIE_MASK; // set RE, TE and RIE bits
  *(serial_port->ControlRegister1) = 0x00;
  
}  

void writeStringToSCI(serialPort *serial_port, char* string) {
    
    int i;
    DisableInterrupts;
    
    // set READ_WRITE to 1 so that the interrupt knows it should be writing
    READ_WRITE = 1;
        
    // store string into rawData array so it can be sent to serial port
    for (i = 0; i < strlen(string); i++) {
    
      rawData[i] = string[i];
    
    }
    writePointer = &rawData[0];
    writeCounter = 1; // counter to keep track of which character to send (start 1 to send second char)
    // send first char to serial
    *(serial_port->DataRegister) = *writePointer; 
    *(serial_port->ControlRegister2) = 0x8C;
    
    // turning on interrupts conitnues the writing process
    EnableInterrupts; 

    // this will only be reached once the writing has finished
    READ_WRITE = 0;
        
    // reset writeCounter for the next time a write to serial needs to run
    writeCounter = 0; 
 
}

void readSerial(serialPort *serial_port) {
  if (*(serial_port->StatusRegister) && SCI0SR1_RDRF_MASK) {      
      rawData[readCounter] = *(serial_port->DataRegister); // store the char from port 0 in a static list
      *(serial_port->DataRegister) = rawData[readCounter];
      if (rawData[readCounter] == 13) {
        carriageFlag = 1;
      }
      readCounter ++; // update the readCounter to be ready for next char
    } 
}

void writeSerial(serialPort *serial_port) {
  // stop writing after the last char has been written
  //if (rawData[writeCounter] == 13) {
  if (*writePointer == 13) {
    *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK; // disable write interrupts
  }
  while((*(serial_port->StatusRegister) & SCI1SR1_TDRE_MASK) == 0){
    // wait here
  }
  //*(serial_port->DataRegister) = rawData[writeCounter]; // store the char in a list
  *(serial_port->DataRegister) = *writePointer; // store the char in a list
  //writeCounter ++; // update the value at the pointer to index
  writePointer++;
}

void processSerialInput(void) {
  
  DisableInterrupts; // disable interrupts whilst data is being dealt with

  if (rawData[0] == 0) {
    // do stuff with commands  
  } 
  else if (rawData[0] == 1) {
    // do stuff with tune  
  }
  
  resetNewInput();
    
}

void resetNewInput(void) {

  carriageFlag = 0;
  readCounter = 0;
  READ_WRITE = 0;
  writeCounter = 0;
  
  EnableInterrupts; // re-enable interrupts  
}
