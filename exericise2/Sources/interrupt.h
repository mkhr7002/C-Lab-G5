#ifndef TIMERS_HEADER
#define TIMERS_HEADER


// function to initialise the timer
void Init_SCI0 (void);

// Timer interrupt definition
__interrupt void SCI0_ISR(void);


#endif
