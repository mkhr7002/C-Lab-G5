#ifndef SERIAL_HEADER
#define SERIAL_HEADER



// function to intialise serial port

void Init_SCI (void);

// serial port read interrupt definition

__interrupt void SCI0_ISR(int readData[], int* index);

__interrupt void SCI1_ISR(int readData[], int* index);

#endif