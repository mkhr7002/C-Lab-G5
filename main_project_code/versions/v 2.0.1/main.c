#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "functions.h"
#include "serial.h"

serialPort SCI0 = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};
serialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};

void main(void) {
  
  // initialise serial ports SCI0 and SCI1 to trigger interupts
  
  EnableInterrupts;

  initialiseSerialPort(&SCI0);
  
  // call function to send "Initalisation Successful"
  // to the terminal via the serial port
  
  displaySuccessfulInit(&SCI0);
  DisableInterrupts
  // re-initalise ports for serial reading interrupts
  initialiseSerialPort(&SCI0);
  initialiseSerialPort(&SCI1);
  EnableInterrupts 

  while (1) {
    _FEED_COP(); /* feeds the dog */

    while (carriageFlag != 1) {
      _FEED_COP(); /* feeds the dog */
  
    }
    processSerialInput();  
  }

  
  /* please make sure that you never leave main */
}

//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */

__interrupt void SCI0_ISR(void) {
  
  if (READ_WRITE == 0) {
    readSerial(&SCI0);
    if (rawData[readCounter] == 13) {
      carriageFlag = 1;
    }
  }
  else if (READ_WRITE == 1) {
    writeSerial(&SCI0);
  }
      
} 
    

__interrupt void SCI1_ISR(void) {
  
  if (READ_WRITE == 0) {
    readSerial(&SCI1);
    if (rawData[readCounter] == 13) {
      carriageFlag = 1;
    }
  }
  else if (READ_WRITE == 1) {
    if (SCI1SR1 & SCI1SR1_TDRE_MASK) {
      writeSerial(&SCI1);
    }
  }
      
} 