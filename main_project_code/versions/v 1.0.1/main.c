#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "functions.h"

void main(void) {
  
  // initialise serial ports SCI0 and SCI1 to trigger interupts
  
  EnableInterrupts;
  initialiseSerialPorts();
  
  // call function to send "Initalisation Successful"
  // to the terminal via the serial port
  int processedData[SERIAL_BUFFER];
  processedData = processData();
  displaySuccessfulInit(data); 

  

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
