#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "interrupt_new.h"

//type something less than 100 characters on serial terminal and recieve identical reply immediately

void setting_serial(void) 
{
  // Set baud rate to 9600
  SCI0BDL = 0x9C;
  SCI0BDH = 0;
  
  // No fancy stuff needed
  SCI0CR1 = 0;
  
  // 2C = 0010110, Enable receive interrupt, transmit, receive
  SCI0CR2 = 0x2C;
}

void main() 
{

  
  

  setting_serial();     // setting serial port
  EnableInterrupts; // Enabling Interrupts
  

  
  for(;;){
    _FEED_COP(); 
  }
}
