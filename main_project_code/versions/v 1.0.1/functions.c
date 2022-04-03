#include "serial.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


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
    // permit the use of SCI1 to send bits
    SCICR2 =   
    
    char* string = "Initalisation Successful\r";
    
    // store string into readData array which will be overwritten later
    
    for (int i = 0; i < strlen(string); i++) {
    
      readData[i] = string[i];
    
    }
      
    i = 0;
    
    while (i < strlen(string)) {
    
    // if a char is ready to be sent, send one
      
    if (SCISR1 && SCI1SR1_TDRE_MASK == True) {
      
      SCIDRL = readData[i];
      i++;  
        
    }
}









// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */

// pass a list of ints to the interrupt
// as well as a pointer to a memory address containing an index
// this is as the main code will not know an interrupt has occured

__interrupt void SCI0_ISR(int readData[], int* index) {
    
      readData[index] = SCI0DRL; // store the char in a list
      &index ++; // update the value at the pointer to index
      
} 
    

__interrupt void SCI0_ISR(int readData[], int* index) {
    
      readData[index] = SCI0DRL; // store the char in a list
      &index ++; // update the value at the pointer to index
}
