#include "string.h"
#include "functions.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */
#include <hidef.h>
// set up the serial ports

extern int readCounter; // counter to use for reading in data from serial
extern int writeCounter; // counter to use for writing in data from serial
extern int READ_WRITE; // constant used to determine whether the port will be reading/writing
extern int carriageFlag; // constant used to determine end of string

extern char* writePointer;

extern char rawData[SERIAL_BUFFER]; // list to store characters which are read/sent

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
    *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_SCTIE_MASK;
    
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
  //*(serial_port->DataRegister) = 16;
  //writeCounter ++; // update the value at the pointer to index
  writePointer++;
  *(serial_port->StatusRegister) &= ~SCI1SR1_TDRE_MASK;
}

void processSerialInput(serialPort *serial_port) {
  
  int flag = 0;      // set tune flag to 0 = ready to receive string
  
  DisableInterrupts; // disable interrupts whilst data is being dealt with

  if (rawData[0] == 0) {
    // do stuff with commands  
  } 
  // play tune
  else if (rawData[0] == 1) {
    
    flag = 1;                            // flag = 1 --> tune being played - cannot receive another string
    flag = playTune(serial_port);        // playTune returns 0 --> once function is finished, ready to receive another tune
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


int playTune(serialPort *serial_port) {
  
  int tuneBuffer = 10;
  int arrLen;
  int timeCounter;
  int tuneCounter;
  int i = 0;
  int j = 0;
  int time = 0;
  char *string = "The song will take timer counts to finish"; // string being sent to serial port
  
  if (strlen(rawData) % 2 != 0) {                   // making data array is divisible by 2 so it can be split into tune and time arrays
    arrLen = (strlen(rawData)/2) + 1;
  } 
  else {
    arrLen = (strlen(rawData)/2);                   // if array has an odd number of elements, add 1 to the length
  }
  
  for (j = 0; j < arrLen; i++) {
      time = time + (rawData[2*i + 1] * tuneBuffer * rawData[2*i] * rawData[2*i]);  // calculating the full number of times the loop loops
  }
    
  writeStringToSCI(serial_port, string);            // send this time to the serial port in message
  DDRT =0xFF;                                       // set port T as output
  PTT = 0x00;                                       // clear port T
  
  for (i = 0; i < arrLen; i++){                     // iterate through delay arrays
    timeCounter = rawData[2*i] * rawData[2*i];      // create unique large time values - this is how long the tune will play for
    
   while (timeCounter >= 0)                        // loop while time delay >= 0
    tuneCounter = rawData[2*i + 1] * tuneBuffer;   // this is the counter between toggling speaker on and off - different times create different tunes
             
    if (rawData[2*i+1] == ' ') {                   // if there is a space in the 'tune' position of rawData, disable speaker so that it is silent
      PTT =0x00;
    } 
    else {
      PTT ^=  (1<<5);                              // toggle bit 5 of P (PT5) - toggle speaker on/off  
    }
                                                   
    while (tuneCounter >= 0) {                     // loop while tune counter >= 0
      tuneCounter--;                                 // decrement tune delay
    }
   
    timeCounter--;                                  // decrement time delay
   }  
  }
  
  return 0;                                       // return 0 for to reset tune flag
}
