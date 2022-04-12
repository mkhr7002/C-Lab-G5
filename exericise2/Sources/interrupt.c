#include "interrupt.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */

extern int index;
extern int size;
extern char sentence[];

void Init_SCI0 (void) {
  // the string is at around spc $1000
  	SCI0BDH = 0x00;
	SCI0BDL = 0x9C;
	SCI0CR1 = 0x00;		/*configuring the control registers. dont enable anything unnecessary...*/
	SCI0CR2 = 0x2C;     /*receiver interrupt enabled,8C is transmitter interrupts only 10001100, 2C is reciever interrupts only 00101100*/
	//SCI0CR2 = 0x8C;	
}


void Write_SCI0 (void) {

	SCI0DRL = sentence[index];					//write next byte in string to serial
	index++;
	if (index == size)							//if no more bytes
	{
		index = 0;								//reset variables
		
		SCI0CR2 = 0x2C;							//disable transmit interrupts, enable receive interrupts
	}
}

void Read_SCI0 (void) {	

  	sentence[index] = SCI0DRL;					//read byte from serial into next available space
	index++;
	if (sentence[index - 1] == 0x0D)			//if byte was a carriage return
	{
		size = index;							//set variables
		index = 0;
		SCI0CR2 = 0x8C;							//disable receive interrupts, enable transmit interrupt
	}	
}


// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void SCI0_ISR(void) { 
  
  //what to do?
  if ((SCI0CR2 & 0x80) && (SCI0SR1 & 0x80))//if interrupt triggered by TDRE (so we know we are transmitting) and TDRE flag is active (prevents spam reading/writing),
  {
  	Write_SCI0();//write byte to serial
  }
  else if ((SCI0CR2 & 0x20) && (SCI0SR1 & 0x20))//if interrupt triggered by RDRE and RDRE flag is active,
  {
  	Read_SCI0();//read byte from serial	
  }
}
