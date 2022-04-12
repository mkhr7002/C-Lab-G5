#include "interrupt_new.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


char buffer[500];
int bufLength = 0;
int i;


char invalidString[17] = "Invalid command\n\r";   //response messages.
char ledString[5] = "led\n\r";
char musicString[12] = "play music\n\r";

int output; //int, used to determine what response message to print. 

int cur = 0;
char* character;
char* string;
  

// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void SCI0_ISR(void) {

  //How to use: 
  //Toggle LED: "l <PortB buffer content integer>" eg. "l 8"
  
 
  // Serial read mode: check if data is received,
  if (SCI0SR1 & 0x20) 
  {
    // Look for a carriage return
    if (SCI0DRL == 0x0D) 
    {
        buffer[bufLength]= '\0';   //add null byte to terminate buffer
        character = strtok(buffer, " \0"); //split the buffer into command parts
        character = strtok(NULL, "\0");
           
        if( buffer[0] == 'l'){    //if command = l
            
           if(character == NULL){      //set response message
              output = 0;
           } 
           else
           { 
              output = 1;
              
           }
        }
        else if( buffer[0] == 'm'){  //same
           
           if(character == NULL)
           {
              output = 0;
           } 
           else
           {
              output = 2;                 
           }
        }
        else
        {
            output = 0;
        }
        
        // Reset buffer, and switch to serial print mode
        bufLength = 0;
        SCI0CR2 = 0x8C;
    }
     // Store each character of sentence in buffer
    else
    {
      buffer[bufLength] = SCI0DRL;
      bufLength++;
    }
  } 
  //Serial print mode: check if can send data
  else if (SCI0SR1 & 0x80) 
  {
    //print the corresponding message until finished, then switch back to serial read mode
    if (output == 0)
    {
      SCI0DRL = invalidString[cur];
      cur++;
      if (cur >= 17) 
      {
        cur = 0;
        SCI0CR2 = 0x2C;
      }
    } else if (output == 1)
    {
      SCI0DRL = ledString[cur];
      cur++;
      if (cur >= 5) 
      {
        cur = 0;
        SCI0CR2 = 0x2C;
      }
    } else if (output == 2)
    {
      SCI0DRL = musicString[cur];
      cur++;
      if (cur >= 12) 
      {
        cur = 0;
        SCI0CR2 = 0x2C;
      }
    }
    
    
  }
}
