#include "serial.h"
#include "string.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */

#define SERIAL_BUFFER 100

static int readCounter = 0; // counter to use for reading in data from serial
static int writeCounter = 0; // counter to use for writing in data from serial
static int data[SERIAL_BUFFER]; // list to store characters which are read/sent
static int READ_WRITE = 0; // constant used to determine whether the port will be reading/writing

// set up the serial ports
void initaliseSerialPorts (void) {
  
  // clear the bits in SCI0CR1 and SCI1CR1
  SCI0CR1 = 0x00;
  SCI1CR1 = 0x00;
  
  // turn on receive interrupt enable bit, transmitter enable bit and receiver enable bit
  
  SCICR2  = 0x20;
  
  /* 
  SET THE BAUD RATE
  BRParameter = 24 x 10^9 / 16 / baud rate
  baud rate = 9600
  BRParameter = 156250
  */
  
  asm(
        movb    #156,SCI1BDL        // FIX THIS
  )
}

void displaySuccessfulInit(int readData[]) {
    
    // clear bits in SCI1CR1
    SCI1CR1 = 0x00;
    // permit the use of SCI to trigger interrupts when a new bit can be transmitted
    SCICR2 = 0x88;  
    READ_WRITE = 1;
    char* string = "Initalisation Successful\r";
    
    // store string into readData array so it can be sent to serial port
    
    for (int i = 0; i < strlen(string); i++) {
    
      readData[i] = string[i];
    
    }
  
    // THIS HAS TO CHANGE TO USE INTERRUPTS TO KNOW WHEN A NEW CHARACTER CAN BE WRITTEN  
    writeCounter = 0; // counter to keep track of which character to send
    while (writeCounter < strlen(string)) {
      
    }
}




// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */

// pass a list of ints to the interrupt
// as well as a pointer to a memory address containing an index
// this is as the main code will not know an interrupt has occured

__interrupt void SCI0_ISR(void) {
  
  if (READ_WRITE == 0) {
    
    data[readCounter] = SCI0DRL; // store the char in a list
    readCounter ++; // update the value at the pointer to index
    
  }
  else if (READ_WRITE == 1) {
    // WRITE
    // SCI0DRL = data[writeCounter];
    // writeCounter += 1
  }
      
} 
    

__interrupt void SCI1_ISR(void) {
  
  if (READ_WRITE == 0) {
    
    data[readCounter] = SCI1DRL; // store the char in a list
    readCounter ++; // update the value at the pointer to index
    
  }
  else if (READ_WRITE == 1) {
    // WRITE
    // SCI1DRL = data[writeCounter];
    // writeCounter += 1
  }
      
} 
