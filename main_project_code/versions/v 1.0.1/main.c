#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "functions.h"

#define SERIAL_BUFFER 40


void main(void) {
  
  // initialise serial ports SCI0 and SCI1 to trigger interupts
  
  EnableInterrupts;
  initialiseSerialPorts();
  
  // call function to send "Initalisation Successful"
  // to the terminal via the serial port
  
  displaySuccessfulInit(data); 

  

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
