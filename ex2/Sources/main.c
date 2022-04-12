#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


void setting_serial(void);
__interrupt void serial_ISR(void);
void invalidInput();

char buffer[100];
int stringLength = 0;



void main(void) {

 
  setting_serial();     // setting serial port
  


	EnableInterrupts;
	
	DDRB= 0xFF;   // Port B output
	PTJ = 0x00;   // enable LEDs
	


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

void setting_serial(void) 
{
  // Set baud rate to 9600
  SCI1BDL = 0x9C;
  SCI1BDH = 0;
  
  // SCICR1 will not be used in this question
  SCI1CR1 = 0;
  
  // Enable receive interrupt, transmit, receive by set the register to 0010110.
  SCI1CR2 = 0x2C;
}


void invalidInput(){
    
    int i;
    char output[16] = " invalidInput\n\r";
    
     for (i = 0; i < 15; i++) 
        {
          // compare with Transmit Data Register Empty Flag
          while(!(SCI1SR1 & 0x80));
          SCI1DRL = output[i];
        } 
     
       
}

__interrupt void serial_ISR(void) 
{
  int i;
  char* words;
  char* string;
  // Check if data is received
  if (SCI1SR1 & 0x20) 
  {
    // compare with carriage return
    if (SCI1DRL == 0x0D) 
    {   
        
        // Check the Transmit Data Register Empty Flag
        while(!(SCI1SR1 & 0x80));
           
        if( buffer[0] == 'l'){
        
           //buffer[strlen(buffer)-1]= '\n';
           string = buffer;
           words = strtok(string, " ");
           words = strtok(NULL, " ");
           words[strlen(words)] = ':';
           words[strlen(words)] = 'L';
           words[strlen(words)] = 'E';
           words[strlen(words)] = 'D';
            
           words[strlen(words)] = '\n';
           words[strlen(words)] = '\r';
            
            if(words == NULL){
               invalidInput();
            } else{                                     
                for(i = 0; i!= strlen(words);i++){
                  while(!(SCI1SR1 & 0x80));
                  SCI1DRL = words[i];
                }
                
                PORTB = atoi(words);
            }
                                  
        }
        else{
            invalidInput();
        }
        // Reset buffer
        memset(buffer, '\0' , sizeof(buffer));
        stringLength = 0;

     }
    
    // Store each character of sentence in buffer
    else
    {
      buffer[stringLength] = SCI1DRL;
      stringLength = stringLength + 1;
    }
   
  }
}

