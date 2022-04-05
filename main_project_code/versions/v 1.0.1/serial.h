#ifndef SERIAL_HEADER
#define SERIAL_HEADER

#define SERIAL_BUFFER 100

// serial port read interrupt definition

__interrupt void SCI0_ISR(void);

__interrupt void SCI1_ISR(void);

#endif
