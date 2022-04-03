#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



void main(void) {
  /* put your own code here */

	EnableInterrupts;
  
  // function to initialise serial ports SCI0 and SCI1
  initialiseSerialPorts(); 

  // declare required variables
  // variables required for reading and storing data
  int readData[20];
  int counter = 0;
  int *index = &counter;
  





  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
